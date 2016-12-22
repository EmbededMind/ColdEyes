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
		mId, mConfig.mNameId, mConfig.mIsCameraOn, mConfig.mIsRecordEnabled, 
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
	return this->mId;
}



char* CPort::GetMac()
{
	return this->mMac;
}



UINT16 CPort::GetNameIndex()
{
	return this->mNameIndex;
}



void CPort::SetId(UINT16 id)
{
	this->mId   = id;
}



void CPort::SetMac(char* mac)
{
	strcpy_s(mMac, mac);
}



void CPort::SetNameIndex(UINT16 inx)
{
	this->mNameIndex  = inx;
}
