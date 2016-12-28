#include "stdafx.h"
#include "Device\Port.h"
#include "Database\DBHelper.h"

CPort::CPort()
{

}



CPort::~CPort()
{

}



void  CPort::BindCamera(CCamera* pCamera)
{
	this->mCamera  = pCamera;
}



void CPort::CommitUpdate()
{
	char formatValues[100];
	char condition[64];

	CDBHelper&  helper = CDBHelper::GetInstance();

	sprintf_s(formatValues, "id = %d,name_id = %d, cam_on = %d, record_on = %d, aw_on = %d, vol = %d",
		mConfig.mId, mConfig.mNameId, mConfig.mIsCameraOn, mConfig.mIsRecordEnabled, 
		mConfig.mIsAutoWatchEnabled, mConfig.mVol);
	
	sprintf_s(condition, "pos = %d", mPos);
	helper.Update("port_config", formatValues, condition);
}



CCamera* CPort::GetBindedCamera()
{
	return this->mCamera;
}



UINT16 CPort::GetId()
{
	return mConfig.mId;
}



char* CPort::GetMac()
{
	return this->mMac;
}



const CString& CPort :: GetName()
{
	return PortNames[mConfig.mId];
}



UINT16 CPort::GetNameId()
{
	return mConfig.mNameId;
}



void CPort::GetConfig(CPortConfig* pConfig)
{
	pConfig->mIsAutoWatchEnabled  = mConfig.mIsAutoWatchEnabled;
	pConfig->mIsCameraOn  = mConfig.mIsCameraOn;
	pConfig->mIsRecordEnabled  = mConfig.mIsRecordEnabled;
	pConfig->mNameId  = mConfig.mNameId;
	pConfig->mVol  = mConfig.mVol;
}



void CPort::SetConfig(CPortConfig* pConfig, UINT16 mask)
{
	if (mask & PORT_CONFIG_AW) {
		mConfig.mIsAutoWatchEnabled  = pConfig->mIsAutoWatchEnabled;
	}

	if (mask & PORT_CONFIG_CAM) {
		mConfig.mIsCameraOn  = pConfig->mIsCameraOn;
	}

	if (mask & PORT_CONFIG_RD) {
		mConfig.mIsRecordEnabled  = pConfig->mIsRecordEnabled;
	}

	if (mask & PORT_CONFIG_NAME) {
		mConfig.mNameId  = pConfig->mNameId;
	}

	if (mask & PORT_CONFIG_VOL) {
		mConfig.mVol  = pConfig->mVol;
	}
}


void CPort::SetId(UINT16 id)
{
	mConfig.mId   = id;
}



void CPort::SetMac(char* mac)
{
	strcpy_s(mMac, mac);
}



void CPort::SetNameId(UINT16 inx)
{
	mConfig.mNameId  = inx;
}
