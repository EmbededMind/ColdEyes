#pragma once
#include "stdafx.h"
#include <string>

#define DEFUT_SYSCONFIG_BOATNAME              "SealedGhost"
#define DEFUT_SYSCONFIG_BRTNESS               3
#define DEFUT_SYSCONFIG_VOL                   4
#define DEFUT_SYSCONFIG_AL                    true
#define DEFUT_SYSCONFIG_AW                    true
#define DEFUT_SYSCONFIG_AWBT                  0
#define DEFUT_SYSCONFIG_AWET                  120
#define DEFUT_SYSCONFIG_AS                    true
#define DEFUT_SYSCONFIG_ASID                  1
#define DEFUT_SYSCONFIG_ASSEC                 10

class CSystemConfig 
{
private	:
	CSystemConfig();
	~CSystemConfig();
	CSystemConfig(const CSystemConfig& instance){}

private:
	std::string  mBoatName;	        //��������
	UINT16       mBrtness;	        //����
	UINT16       mVol;	            //����

	bool         mAlIsOn;           //�����ƿ���

	bool         mAwIsOn;           //�Զ���������
	DWORD        mAwBeginTime;      //�Զ�������ʼʱ��
	DWORD        mAwEndTime;        //�Զ���������ʱ��

	bool         mAsIsOn;           //����������
	UINT16       mAsId;             //������ѡ�� ��1 or 2��
	UINT16       mAsDefaultSec;     //Ĭ�ϱ�����ʱ��
	UINT16       mAsSec;            //�Զ��屨����ʱ��

public :
	static CSystemConfig& GetInstance();

	void         CommitUpdate();
	void         CommitAutoWatchUpdate();
	void         CommitAlarmUpdate();
	void         CommitSystemUpdate();
};