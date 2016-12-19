#include "stdafx.h"

#include "Device\Camera.h"


CCamera::CCamera()
{
	mLoginId  = -1;
}



CCamera::~CCamera()
{

}



bool  CCamera::Login()
{
	int errorCode  = 0;

	long ret  = H264_DVR_Login(mIp,  mPort, mUserName, mPassword, &mInfo, &errorCode);

	if (ret > 0) {
		mLoginId  = ret;
		return true;
	}
	else {
		Print("Camera %s login failed.Error code is:%d", mIp,  errorCode);
		return false;
	}
}


bool  CCamera::Logout()
{
	if (mLoginId > 0) {
		if (H264_DVR_Logout(mLoginId)) {
			mLoginId  = -1;
			return true;
		}
		else {
			Print("Camera %s logout failed.Error code is:%d", mIp, H264_DVR_GetLastError());
			return false;
		}
	}
	else {
		return true;
	}
}



void CCamera::SetCommonNetConfig(SDK_CONFIG_NET_COMMON_V2* pConfig)
{
	memcpy_s(&mCommonNetConfig, sizeof(SDK_CONFIG_NET_COMMON_V2), pConfig, sizeof(SDK_CONFIG_NET_COMMON_V2));
	IPNumberToStr(pConfig->HostIP.c,  mIp);
}



