#include "stdafx.h"

#include "Device\Camera.h"



bool __stdcall cbAlarmInfo(long loginId, char* pBuf, DWORD bufLength, long useData)
{
	if (bufLength == sizeof(SDK_NetAlarmCenterMsg)) {
		SDK_NetAlarmCenterMsg* pMsg  = (SDK_NetAlarmCenterMsg*)pBuf;

		Print("Alarm info:%s  %s", pMsg->nType == SDK_ALARMCENTER_ALARM ? "Alarm":"Log",
		                           pMsg->nStatus == SDK_AC_START ? "start" : "stop");

		return true;
	}

	return false;
}





CCamera::CCamera()
{
	mLoginId  = -1;
	strcpy_s(mUserName, "admin");
	strcpy_s(mPassword, "");
	mPort  = 34567;

	mDeviceInfo.deviceTye  = SDK_DEVICE_TYPE_DVR;	
}



CCamera::~CCamera()
{

}



long  CCamera::GetLoginId()
{
	return mLoginId;
}



bool CCamera::GetParam()
{
	ASSERT(mLoginId > 0);

	DWORD resBytes  = 0;
	long  ret  = H264_DVR_GetDevConfig(mLoginId,  E_SDK_CONFIG_CAMERA, 0,
									(char*)&mParam, sizeof(SDK_CameraParam), &resBytes, 2000);

	if (ret < 0) {
		Print("Get camera param failed:%d", H264_DVR_GetLastError());
		return false;
	}

	return true;
}



bool  CCamera::Login()
{
	int errorCode  = 0;

	long ret  = H264_DVR_Login(mIp,  mPort, mUserName, mPassword, &mDeviceInfo, &errorCode);

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



void CCamera::OnCameraLogin()
{
	SetTime(CTime::GetCurrentTime());
}



void CCamera::SetCommonNetConfig(SDK_CONFIG_NET_COMMON_V2* pConfig)
{
	memcpy_s(&mCommonNetConfig, sizeof(SDK_CONFIG_NET_COMMON_V2), pConfig, sizeof(SDK_CONFIG_NET_COMMON_V2));
	IPNumberToStr(pConfig->HostIP.c,  mIp);
}



bool CCamera::SetParam()
{
	ASSERT(mLoginId > 0);

	long ret  = H264_DVR_SetDevConfig(mLoginId, E_SDK_CONFIG_CAMERA, 0, 
								(char*)&mParam, sizeof(SDK_CameraParam), 2000);

	if (ret < 0) {
		Print("Set camera param failed:%d", H264_DVR_GetLastError());
		return false;
	}

	return true;
}



bool CCamera::SetTime(CTime& time)
{
	SDK_SYSTEM_TIME sdkTime;
	sdkTime.year      = time.GetYear();
	sdkTime.month     = time.GetMonth();
	sdkTime.day       = time.GetDay();
	sdkTime.wday      = time.GetDayOfWeek();
	sdkTime.hour      = time.GetHour();
	sdkTime.minute    = time.GetMinute();
	sdkTime.second    = time.GetSecond();
	sdkTime.isdst     = 0;

	if (mLoginId > 0) {
		if (H264_DVR_SetSystemDateTime(mLoginId, &sdkTime)) {
			return true;
		}
		else {
			Print("设置摄像头时间失败:%d", H264_DVR_GetLastError());
			return false;
		}
	}
	else {
		Print("登录 id 无效");
	}

	return false;
}



bool CCamera::StartAlarmCenterListen()
{
	if (H264_DVR_StartAlarmCenterListen(mPort, cbAlarmInfo, (DWORD)this)) {
		return true;
	}
	else {
		Print("Start alarm center listen failed:%d", H264_DVR_GetLastError());
		return false;
	}
}



bool CCamera::StopAlarmCenterListen()
{
	if (H264_DVR_StopAlarmCenterListen()) {
		return true;
	}
	else {
		Print("Stop alarm center listen failed:%d", H264_DVR_GetLastError());
		return false;
	}
}


bool CCamera::SubscribeAlarmMessage()
{
	if (this->mLoginId > 0) {
		if (H264_DVR_SetupAlarmChan(mLoginId)) {
			return true;
		}
		else {
			Print("Subscribe alarm message failed:%d", H264_DVR_GetLastError());
		}
	}
	else {
		Print("登录 id 无效");
	}

	return false;
}



bool CCamera::UnsubscribeAlarmMessage()
{
	if (this->mLoginId > 0) {
		if (H264_DVR_CloseAlarmChan(mLoginId)) {
			return true;
		}
		else {
			Print("Unsubscribe alarm message failed:%d", H264_DVR_GetLastError());
		}
	}
	else {
		Print("登录 id 无效");
	}

	return false;
}