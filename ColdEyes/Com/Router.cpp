#include "stdafx.h"

#include "Com\Router.h"

CRouter::CRouter() { InitializeCriticalSection(&mCS); }


CRouter::~CRouter() { DeleteCriticalSection(&mCS); }


void CRouter::HandleData(UINT8* pRxData, size_t length)
{
	if (length <= 20) {
		/*memcpy(mRxCache[mRxCursor], pRxData, length);*/
		if (pRxData[0] == 0x24 && pRxData[16] == 0xfd) {
			// if CRC ok
			if (CheckCRC32(pRxData, 12))
			{
				int cmd = pRxData[3];
				if (cmd < 7)
				{
					IDataHandler* pHandler = mHandleres[cmd];
					pHandler->HandleData(&pRxData[3], 13);
				}
			}
		}
	}
	else {
		Print("Rx size out of range");
	}
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
	EnterCriticalSection(&mCS);
	UINT8 tmp[20];

	tmp[0]  = 0x24;
	tmp[16] = 0xfd;
	memcpy(&tmp[3], pData, 11);

	uint32_t crc = CRC32Software(pData, 12);
	tmp[12] = (uint8_t)(crc >> 24);
	tmp[13] = (uint8_t)((crc & 0x00ffffff) >> 16);
	tmp[14] = (uint8_t)((crc & 0x0000ffff) >> 8);
	tmp[15] = (uint8_t)(crc & 0x000000ff);

	mSender->WriteToPort(tmp, 17);
	LeaveCriticalSection(&mCS);
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
								  //Length = 1;
	while (Length--) {
		xbit = 1 << 31;
		data = *pData++;
		data &= 0x000000ff;
		//data = 0x44434241;
		//Print("%32x", data);
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
