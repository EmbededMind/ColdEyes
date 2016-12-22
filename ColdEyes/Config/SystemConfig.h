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
	std::string  mBoatName;	        //船舶名称
	UINT16       mBrtness;	        //亮度
	UINT16       mVol;	            //音量

	bool         mAlIsOn;           //报警灯开关

	bool         mAwIsOn;           //自动看船开关
	DWORD        mAwBeginTime;      //自动看船开始时间
	DWORD        mAwEndTime;        //自动看船结束时间

	bool         mAsIsOn;           //报警音开关
	UINT16       mAsId;             //报警音选择 （1 or 2）
	UINT16       mAsDefaultSec;     //默认报警音时长
	UINT16       mAsSec;            //自定义报警音时长

public :
	static CSystemConfig& GetInstance();

	void         CommitUpdate();
	void         CommitAutoWatchUpdate();
	void         CommitAlarmUpdate();
	void         CommitSystemUpdate();
};