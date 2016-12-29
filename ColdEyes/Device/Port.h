#pragma once

#include "stdafx.h"

#include "Device\Camera.h"
#include "Config\PortConfig.h"


#define PORT_CONFIG_CAM   0x0001
#define PORT_CONFIG_RD    0x0002
#define PORT_CONFIG_AW    0x0004
#define PORT_CONFIG_VOL   0x0008
#define PORT_CONFIG_NAME  0x0010
#define PORT_CONFIG_ALL   0x00FF

const  CString PortNames[25] = {
	_T(""),
	_T("摄像机1"),
	_T("摄像机2"),
	_T("摄像机3"),
	_T("摄像机4"),
	_T("摄像机5"),
	_T("摄像机6"),
	_T("船头摄像机"),
	_T("船甲板摄像机"),
	_T("船左舷摄像机"),
	_T("船右舷摄像机"),
	_T("船后方摄像机"),
	_T("船缆绳摄像机"),
	_T("集控台摄像机"),
	_T("监控台摄像机"),
	_T("船长室摄像机"),
	_T("船员室摄像机"),
	_T("一层甲板摄像机"),
	_T("二层甲板摄像机"),
	_T("三层甲板摄像机"),
	_T("四层甲板摄像机"),
	_T("五层甲板摄像机"),
	_T("主机舱摄像机"),
	_T("发电机舱摄像机"),
	_T("罗经甲板摄像机")
};




class CPort
{
public:
	CPort();
	~CPort();


public:
	CPortConfig  mConfig;
	UINT16       mPos;

	void               BindCamera(CCamera* pCamera);

	void               CommitUpdate();

	CCamera*           GetBindedCamera();
	UINT16		       GetId();
	char*		       GetMac();
	const CString&     GetName();
	UINT16		       GetNameId();
	void               GetConfig(CPortConfig* pConfig);

	void               SetConfig(CPortConfig* pConfig, UINT16 mask);
	void		       SetId(UINT16 id);
	void		       SetMac(char* mac);
	void		       SetNameId(UINT16 inx);

private:
	char        mMac[20];

	CCamera*    mCamera;

};