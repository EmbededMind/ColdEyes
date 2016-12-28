#pragma once
#include "stdafx.h"
#include <list>


#include "Pattern\IDataHandler.h"
#include "Com\Router.h"

#include "NetSdk\netsdk.h"

typedef enum {
	DevState_Offline  = 0,
	DevState_PendMac  ,
	DevState_PendCamera,
	DevState_PendLogin,
	DevState_Online
}DeviceState;

class CDeviceDetecter : public IDataHandler 
{
private :
	CDeviceDetecter();
	~CDeviceDetecter();


public:
	SDK_CONFIG_NET_COMMON_V2   mDeviceNetConfig[10];
	DeviceState                mDevicesState[PORT_MAX_NUM];
	int                        mLastScanedDeviceNumber;
	char                       mPendedMac[PORT_MAX_NUM][40];

    static CDeviceDetecter* GetInstance();


	bool         CreateDetectionThread();
	bool         CreateLoginThread();

	SDK_CONFIG_NET_COMMON_V2*         FindDevice(char* mac);
	UINT         GetLoginThreadPid();

	virtual void HandleData(UINT8* pData, size_t length);



	void         PendPortState();



	bool         StartDetect();




private:
	CRouter*     mpRouter;





	bool         mIsNeedAck;

	bool         mIsDetectionThreadAlive;
	bool         mIsLoginThreadAlive;

	CWinThread*  mDetectionThread;
	//CWinThread*  mLoginThread;

	HANDLE       mLoginThread;
	UINT         mLoginThreadPid;

	HANDLE       mTickTimer;
	HANDLE       mAckEvent;
	LARGE_INTEGER  mLiDueTime;

	HANDLE       mDetectionEndEvent;
	HANDLE       mLoginEndEvent;

	HANDLE       mScanDevEvent;
	HANDLE       mLoginDevEvent;
	HANDLE       mLoginEventArray[2];

	char         mCachedMac[40];




	int          mCurrentPortId;
	std::list<int> mPendMacList;

	static 	UINT    DetectionThread(LPVOID); 
	//static  UINT    LoginThread(LPVOID);
};