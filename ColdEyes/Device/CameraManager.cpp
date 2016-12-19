#include "stdafx.h"

#include "Device\CameraManager.h"



UINT __stdcall ScanCamera(PVOID pM)
{
	MSG msg;

	static SDK_CONFIG_NET_COMMON_V2  DeviceConfig[10];
	static int						 ScanLength  = 0;

	while (GetMessage(&msg, 0, 0, 0)) {
		switch (msg.message) {
			case USER_MSG_SCAN_DEV:
			{
				bool hasFound  = false;
				int  i         = 0;

				for (; i < ScanLength; i++) {
					
				}
			}
		}
	}


	return 0;
}




CCameraManager::CCameraManager()
{
	mThreadHandle  = 0;
	mThreadPid  = 0;
	mIsThreadAlive  = false;
}



CCameraManager::~CCameraManager()
{
//  if(mIsThreadAlive)
//	{
//		KillSelf();
//	}
}


bool  CCameraManager::Init()
{
	//mThreadHandle  = (HANDLE)_beginthreadex(NULL, 0, ScanCamera,  NULL,  0, &mThreadPid);
	return false;
}


