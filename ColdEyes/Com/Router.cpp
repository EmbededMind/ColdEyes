#include "stdafx.h"

#include "Com\Router.h"

CRouter::CRouter(){}


CRouter::~CRouter(){}


void CRouter::HandleData(UINT8* pRxData, size_t length)
{
	if (length <= 20) {
		/*memcpy(mRxCache[mRxCursor], pRxData, length);*/
		if (pRxData[0] == 0x24 && pRxData[16] == 0xfd) {
			// if CRC ok
			int cmd   = pRxData[3];
			if (cmd < 7)
			{
				IDataHandler* pHandler  =  mHandleres[cmd];
				pHandler->HandleData(&pRxData[3], 13);
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

	UINT8 tmp[20];

	tmp[0]  = 0x24;
	tmp[16] = 0xfd;

	memcpy(&tmp[3], pData, 11);

	mSender->WriteToPort(tmp, 17);
}



void CRouter::AttachSender(CSerialPort* pSender)
{
	mSender  = pSender;
}