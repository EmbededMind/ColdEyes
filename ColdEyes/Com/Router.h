#pragma once

#include "Pattern\IDataHandler.h"
#include "Com\SerialPort.h"

typedef struct ComDataPacket 
{
	UINT8 data[20];
	UINT8 length;
	bool isUsed;
}ComDataPacket;

class CRouter : public IDataHandler
{
public:
	CRouter();
	~CRouter();

public:
	virtual void HandleData(UINT8* pRxData, size_t length);

	void    RegisterHandler(IDataHandler* pHandler,  UINT8 whatCmd);

	void    SendData(UINT8* pData, size_t length);

	void    AttachSender(CSerialPort* pSender);

	uint32_t CRC32Software(uint8_t *pData, uint16_t Length);
	bool CheckCRC32(uint8_t *pData, uint16_t Length);

	bool Init();
	bool StartThread();
private:	
    CSerialPort*    mSender;
	IDataHandler*   mHandleres[10];

	ComDataPacket   mTxCache[10];
	ComDataPacket   mRxCache[10];

	CRITICAL_SECTION mCSSend;
	CRITICAL_SECTION mCSReceive;

	CWinThread *mRouterThread;
	static UINT RouterThread(LPVOID pParam);
	bool mIsThreadAlive;

	HANDLE mEndThreadEvent;
	HANDLE mSendEvent;
	HANDLE mReceiveEvent;
	HANDLE mEventArray[3];
};