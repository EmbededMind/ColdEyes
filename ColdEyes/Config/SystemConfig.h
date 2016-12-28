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


//bool         mAlIsOn;           //报警灯开关

//bool         mAwIsOn;           //自动看船开关
//DWORD        mAwBeginTime;      //自动看船开始时间
//DWORD        mAwEndTime;        //自动看船结束时间

//bool         mAsIsOn;           //报警音开关
//UINT16       mAsId;             //报警音选择 （1 or 2）
//UINT16       mAsDefaultSec;     //默认报警音时长
//UINT16       mAsSec;            //自定义报警音时长
#define     SYS_CONFIG_AL                0x0001
#define     SYS_CONFIG_AS                0x0002
#define     SYS_CONFIG_ASID              0x0004
#define     SYS_CONFIG_ASDFTSEC          0x0008
#define     SYS_CONFIG_ASSEC             0x0010
#define     SYS_CONFIG_ALARM_ALL         0x001F

#define     SYS_CONFIG_AW                0x0020
#define     SYS_CONFIG_AWBT              0x0040
#define     SYS_CONFIG_AWET              0x0080
#define     SYS_CONFIG_AW_ALL            0x00E0

#define     SYS_CONFIG_NAME              0x0100
#define     SYS_CONFIG_BRT               0x0200
#define     SYS_CONFIG_VOL               0x0400



typedef struct {
	bool            isAlarmSoundOn;
	bool            isAlarmLightOn;
	UINT16          alarmSoundId;
	UINT16          alarmSoundSec;
	UINT16          defutAlarmSoundSec;	
}SystemAlarmConfig;



typedef struct {
	bool         isAutoWatchOn;
	DWORD        autoWatchBeginTime;
	DWORD        autoWatchEndTime;
}SystemAutoWatchConfig;



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

	SystemAlarmConfig         mAlarmConfig;
	SystemAutoWatchConfig     mAutoWatchConfig;



public :
	static CSystemConfig& GetInstance();



	void         CommitAutoWatchUpdate();
	void         CommitAlarmUpdate();
	void         CommitSystemUpdate();
	void         CommitUpdate();

	void         GetAlarmConfig(SystemAlarmConfig* pConfig);
	void         GetAutoWatchConfig(SystemAutoWatchConfig* pConfig);
	CString&     GetBoatName();
	UINT16       GetBrightness();
	UINT16       GetVolumn();

	void         SetAlarmConfig(SystemAlarmConfig* pConfig, UINT16 mask);
	void         SetAutoWatchConfig(SystemAutoWatchConfig* pConfig, UINT16 mask);
	void         SetBoatName(std::string& name);
	void         SetBrightness(UINT16 brtness);
	void         SetVolumn(UINT16 vol);
};