#include "stdafx.h"

#include "Com\Router.h"

CRouter::CRouter() { 
	InitializeCriticalSection(&mCSSend);
	InitializeCriticalSection(&mCSReceive);
}


CRouter::~CRouter() { 
	DeleteCriticalSection(&mCSSend);
	InitializeCriticalSection(&mCSReceive);
	SetEvent(mEndThreadEvent);
}


void CRouter::HandleData(UINT8* pRxData, size_t length)
{
	EnterCriticalSection(&mCSReceive);
	for (int i = 10; i < 10; i++)
	{
		if (mRxCache[i].isUsed)
		{
			memcpy(mRxCache[i].data, pRxData, length);
			mRxCache[i].length = length;
			mRxCache[i].isUsed = false;
			SetEvent(mReceiveEvent);
			LeaveCriticalSection(&mCSReceive);
			return;
		}
	}
	LeaveCriticalSection(&mCSReceive);
	return;
}


void CRouter::RegisterHandler(IDataHandler* pHandler, UINT8 whatCmd)
{
	if (whatCmd < 10) {
		mHandleres[whatCmd]  = pHandler;
	}
}



void CRouter::SendData(UINT8* pData, size_t length)
{
	//ASSERT(mSender £¡= NULL);
	EnterCriticalSection(&mCSSend);
	for (int i = 0; i < 10; i++)
	{
		if (mTxCache[i].isUsed)
		{
			memcpy(&mTxCache[i].data, pData, length);
			mTxCache[i].isUsed = false;
			SetEvent(mSendEvent);
			LeaveCriticalSection(&mCSSend);
			return;
		}
	}
	LeaveCriticalSection(&mCSSend);
	return;
}



void CRouter::AttachSender(CSerialPort* pSender)
{
	mSender  = pSender;
}

uint32_t CRouter::CRC32Software(uint8_t * pData, uint16_t Length)
{
	DWORD dwPolynomial = 0x04c11db7;
	DWORD    xbit;
	DWORD    data;
	DWORD    CRC = 0xFFFFFFFF;    // init
								  
	while (Length--) {
		xbit = 1 << 31;
		data = *pData++;
		data &= 0x000000ff;
		for (int bits = 0; bits < 32; bits++) {
			if (CRC & 0x80000000) {
				CRC <<= 1;
				CRC ^= dwPolynomial;
			}
			else
				CRC <<= 1;
			if (data & xbit)
				CRC ^= dwPolynomial;

			xbit >>= 1;
		}
	}
	return CRC;
}

bool CRouter::CheckCRC32(uint8_t * pData, uint16_t Length)
{
	uint32_t crc = CRC32Software(pData, Length);
	if (pData[Length] != (uint8_t)(crc >> 24))
		return false;
	if (pData[Length + 1] != (uint8_t)((crc & 0x00ffffff) >> 16))
		return false;
	if (pData[Length + 2] != (uint8_t)((crc & 0x0000ffff) >> 8))
		return false;
	if (pData[Length + 3] != (uint8_t)(crc & 0x000000ff))
		return false;
	return true;
}

bool CRouter::Init()
{
	if (mSendEvent != NULL)
		ResetEvent(mSendEvent);
	else
		mSendEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mReceiveEvent != NULL)
		ResetEvent(mReceiveEvent);
	else
		mReceiveEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	mEventArray[0] = mEndThreadEvent;
	mEventArray[2] = mSendEvent;
	mEventArray[1] = mReceiveEvent;

	for (int i = 0; i < 10; i++)
	{
		mRxCache[i].isUsed = true;
		mTxCache[i].isUsed = true;
	}
	return false;
}

bool CRouter::StartThread()
{
	if (!(mRouterThread = AfxBeginThread(RouterThread, this)))
		return false;
	return true;
}

UINT CRouter::RouterThread(LPVOID pParam)
{
	CRouter *pThis = (CRouter*)pParam;
	DWORD Event = 0;
	pThis->mIsThreadAlive = true;
	for (;;)
	{
		Event = WaitForMultipleObjects(3, pThis->mEventArray, FALSE, INFINITE);
		switch (Event)
		{
		case 0:
			pThis->mIsThreadAlive = false;
			AfxEndThread(10);
			break;
		case 1:
			ResetEvent(pThis->mReceiveEvent);
			EnterCriticalSection(&pThis->mCSReceive);
			for (int i = 0; i < 10; i++)
			{
				if (pThis->mRxCache[i].isUsed)
					continue;
				if (pThis->mRxCache[i].length <= 17) {
					/*memcpy(mRxCache[mRxCursor], pRxData, length);*/
					if (pThis->mRxCache[i].data[0] == 0x24 && pThis->mRxCache[i].data[16] == 0xfd) {
						// if CRC ok
						if (pThis->CheckCRC32(&pThis->mRxCache[i].data[0], 12))
						{
							int cmd = pThis->mRxCache[i].data[3];
							if (cmd < 7)
							{
								IDataHandler* pHandler = pThis->mHandleres[cmd];
								pHandler->HandleData(pThis->mRxCache[i].data, pThis->mRxCache[i].length);
							}
						}
					}
				}
				else {
					Print("Rx size out of range");
				}
				pThis->mRxCache[i].isUsed = true;
			}
			LeaveCriticalSection(&pThis->mCSReceive);
			break;
		case 2:
			ResetEvent(pThis->mSendEvent);
			EnterCriticalSection(&pThis->mCSSend);
			for (int i = i; i < 10; i++)
			{
				if (pThis->mTxCache[i].isUsed)
					continue;
				pThis->mTxCache[i].data[0] = 0x24;
				pThis->mTxCache[i].data[16] = 0xfd;

				uint32_t crc = pThis->CRC32Software(pThis->mTxCache[i].data, 12);
				pThis->mTxCache[i].data[12] = (uint8_t)(crc >> 24);
				pThis->mTxCache[i].data[13] = (uint8_t)((crc & 0x00ffffff) >> 16);
				pThis->mTxCache[i].data[14] = (uint8_t)((crc & 0x0000ffff) >> 8);
				pThis->mTxCache[i].data[15] = (uint8_t)(crc & 0x000000ff);

				pThis->mSender->WriteToPort(pThis->mTxCache[i].data, 17);
				pThis->mTxCache[i].isUsed = true;
				/*uint8_t cmd = pThis->mTxCache[i].data[3];
				Event = WaitForSingleObject(pThis->mReceiveEvent, 500);
				if (Event != WAIT_OBJECT_0)
				{
					for (int i = 0; i < 10; i++)
					{
						if (pThis->mTxCache[i].isUsed)
						{
							pThis->mTxCache[i].data[3] = cmd;
							pThis->mTxCache[i].data[4] = 0xff;
							IDataHandler* pHandler = pThis->mHandleres[cmd];
							pHandler->HandleData(&pThis->mTxCache[i].data[3], 13);
						}
					}
				}*/
			}
			LeaveCriticalSection(&pThis->mCSSend);
			break;
		default:
			break;
		}
	}
	return 0;
}
