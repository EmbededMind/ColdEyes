#include "stdafx.h"
#include "Device\Port.h"
#include "Database\DBHelper.h"


CString PortName[24] = {  //¶ÔÓ¦Ãû×Öid
	_T("ÉãÏñ»ú1"),
	_T("ÉãÏñ»ú2"),
	_T("ÉãÏñ»ú3"),
	_T("ÉãÏñ»ú4"),
	_T("ÉãÏñ»ú5"),
	_T("ÉãÏñ»ú6"),
	_T("´¬Í·ÉãÏñ»ú"),
	_T("´¬¼×°åÉãÏñ»ú"),
	_T("´¬×óÏÏÉãÏñ»ú"),
	_T("´¬ÓÒÏÏÉãÏñ»ú"),
	_T("´¬ºó·½ÉãÏñ»ú"),
	_T("´¬ÀÂÉþÉãÏñ»ú"),
	_T("¼¯¿ØÌ¨ÉãÏñ»ú"),
	_T("¼à¿ØÌ¨ÉãÏñ»ú"),
	_T("´¬³¤ÊÒÉãÏñ»ú"),
	_T("´¬Ô±ÊÒÉãÏñ»ú"),
	_T("Ö÷»ú²ÕÉãÏñ»ú"),
	_T("·¢µç»ú²ÕÉãÏñ»ú"),
	_T("ÂÞ¾­¼×°åÉãÏñ»ú"),
	_T("Ò»²ã¼×°åÉãÏñ»ú"),
	_T("¶þ²ã¼×°åÉãÏñ»ú"),
	_T("Èý²ã¼×°åÉãÏñ»ú"),
	_T("ËÄ²ã¼×°åÉãÏñ»ú"),
	_T("Îå²ã¼×°åÉãÏñ»ú")
};


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

CString & CPort::GetName()
{
	return PortName[mNameIndex - 1];
}

