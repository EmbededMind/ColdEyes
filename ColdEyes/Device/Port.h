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
	_T("�����1"),
	_T("�����2"),
	_T("�����3"),
	_T("�����4"),
	_T("�����5"),
	_T("�����6"),
	_T("��ͷ�����"),
	_T("���װ������"),
	_T("�����������"),
	_T("�����������"),
	_T("���������"),
	_T("�����������"),
	_T("����̨�����"),
	_T("���̨�����"),
	_T("�����������"),
	_T("��Ա�������"),
	_T("һ��װ������"),
	_T("����װ������"),
	_T("����װ������"),
	_T("�Ĳ�װ������"),
	_T("���װ������"),
	_T("�����������"),
	_T("������������"),
	_T("�޾��װ������")
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