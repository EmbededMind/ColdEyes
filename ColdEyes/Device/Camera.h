#pragma once
#include "NetSdk\netsdk.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	H264_DVR_DEVICEINFO			mDeviceInfo;
	SDK_CameraParam				mParam;
	SDK_CameraAbility			mAbility;
	SDK_CONFIG_NET_COMMON_V2	mCommonNetConfig;

	long         GetLoginId();
	bool         GetParam();

	bool         Login();
	bool         Logout();

	void         OnCameraLogin();
	void         SetCommonNetConfig(SDK_CONFIG_NET_COMMON_V2* pCommonNetConfig);
	bool         SetParam();
	bool         SetTime(CTime& time);
	bool         StartAlarmCenterListen();
	bool         StopAlarmCenterListen();
	bool         SubscribeAlarmMessage();
	bool         UnsubscribeAlarmMessage();



private:
	long                        mLoginId;
	char                        mIp[20];
	char                        mUserName[20];
	char                        mPassword[20];
	WORD                        mPort;
};
