#pragma once
#include "NetSdk\netsdk.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	H264_DVR_DEVICEINFO			mInfo;
	SDK_CameraParam				mParam;
	SDK_CameraAbility			mAbility;
	SDK_CONFIG_NET_COMMON_V2	mCommonNetConfig;

	bool         Login();
	bool         Logout();

	void         SetCommonNetConfig(SDK_CONFIG_NET_COMMON_V2* pCommonNetConfig);
	void         SetIp();

private:
	long                        mLoginId;
	char                        mIp[20];
	char                        mUserName[20];
	char                        mPassword[20];
	WORD                        mPort;
};
