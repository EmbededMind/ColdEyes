#include "stdafx.h"

#include "Config\SystemConfig.h"
#include "Database\DBHelper.h"

CSystemConfig::CSystemConfig()
{
	//mBoatName        = DEFUT_SYSCONFIG_BOATNAME;
	//mBrtness         = DEFUT_SYSCONFIG_BRTNESS;
	//mVol             = DEFUT_SYSCONFIG_VOL;
	//mAlIsOn          = DEFUT_SYSCONFIG_AL;
	//mAwIsOn          = DEFUT_SYSCONFIG_AW;
	//mAwBeginTime     = DEFUT_SYSCONFIG_AWBT;
	//mAwEndTime       = DEFUT_SYSCONFIG_AWET;
	//mAsIsOn          = DEFUT_SYSCONFIG_AS;
	//mAsId            = DEFUT_SYSCONFIG_ASID;
	//mAsDefaultSec    = DEFUT_SYSCONFIG_ASSEC;
	//mAsSec           = 0;

	mBoatName          = DEFUT_SYSCONFIG_BOATNAME;
	mBrtness           = DEFUT_SYSCONFIG_BRTNESS;
	mVol               = DEFUT_SYSCONFIG_VOL;
	mAlarmConfig.alarmSoundId  = DEFUT_SYSCONFIG_ASID;
	mAlarmConfig.alarmSoundSec = 0;
	mAlarmConfig.defutAlarmSoundSec  = DEFUT_SYSCONFIG_ASSEC;
	mAlarmConfig.isAlarmLightOn      = DEFUT_SYSCONFIG_AL;
	mAlarmConfig.isAlarmSoundOn      = DEFUT_SYSCONFIG_AS;

	mAutoWatchConfig.isAutoWatchOn   = DEFUT_SYSCONFIG_AW;
	mAutoWatchConfig.autoWatchBeginTime = DEFUT_SYSCONFIG_AWBT;
	mAutoWatchConfig.autoWatchEndTime   = DEFUT_SYSCONFIG_AWET;
}



CSystemConfig::~CSystemConfig()
{

}



CSystemConfig& CSystemConfig::GetInstance()
{
	static CSystemConfig mInstance;
	return mInstance;
}



void CSystemConfig::CommitUpdate()
{
	CommitAutoWatchUpdate();
	CommitAlarmUpdate();
	CommitSystemUpdate();
}



void CSystemConfig::CommitAutoWatchUpdate()
{
	CDBHelper& helper  = CDBHelper::GetInstance();
	char formatValues[100];
	sprintf_s(formatValues, "auto_watch = %d, aw_begin = %d, aw_end = %d", 
					mAutoWatchConfig.isAutoWatchOn,
					mAutoWatchConfig.autoWatchBeginTime,
					mAutoWatchConfig.autoWatchEndTime);
					//mAwIsOn, mAwBeginTime, mAwEndTime);
	helper.Update("sys_config", formatValues);
}



void CSystemConfig::CommitAlarmUpdate()
{
	CDBHelper& helper  = CDBHelper::GetInstance();

	char formatValues[100];
	sprintf_s(formatValues, "alarm_light = %d, alarm_sound = %d, as_id = %d, as_defut_sec = %d,as_sec = %d",
				mAlarmConfig.isAlarmLightOn,
				mAlarmConfig.isAlarmSoundOn,
				mAlarmConfig.alarmSoundId,
				mAlarmConfig.defutAlarmSoundSec,
				mAlarmConfig.alarmSoundSec);				
	helper.Update("sys_config", formatValues);
}



void CSystemConfig::CommitSystemUpdate()
{
	CDBHelper& helper = CDBHelper::GetInstance();

	char formatValues[100];
	sprintf_s(formatValues, "boat_name = '%s', brightness = %d, volumn = %d",
				mBoatName.c_str(), mBrtness, mVol);
	helper.Update("sys_config", formatValues);
}



void CSystemConfig::DumpConfig()
{
	Print("boat_name     %s", mBoatName.c_str());
	Print("brightness    %d", mBrtness);
	Print("volumn        %d", mVol);
}



void CSystemConfig::GetAlarmConfig(SystemAlarmConfig* pConfig)
{
	memcpy_s(pConfig, sizeof(SystemAlarmConfig), &mAlarmConfig, sizeof(SystemAlarmConfig));
}



void CSystemConfig::GetAutoWatchConfig(SystemAutoWatchConfig* pConfig)
{
	memcpy_s(pConfig, sizeof(SystemAutoWatchConfig), &mAutoWatchConfig, sizeof(SystemAutoWatchConfig));
}



void CSystemConfig::GetBoatName(CString& name)
{
	name = mBoatName.c_str();
}



UINT16 CSystemConfig::GetBrightness()
{
	return mBrtness;
}



UINT16 CSystemConfig::GetVolumn()
{
	return mVol;
}



void CSystemConfig::LoadConfig()
{
	CDBHelper& helper = CDBHelper::GetInstance();
	SQLiteStatement* stmt = helper.Query("sys_config", "*");
	if (stmt->NextRow()) {
		mBoatName = stmt->ValueString(0);
		mBrtness = stmt->ValueInt(1);
		mVol = stmt->ValueInt(2);
		mAlarmConfig.isAlarmLightOn = stmt->ValueInt(3);
		mAutoWatchConfig.isAutoWatchOn = stmt->ValueInt(4);
		mAutoWatchConfig.autoWatchBeginTime = stmt->ValueInt(5);
		mAutoWatchConfig.autoWatchEndTime = stmt->ValueInt(6);
		mAlarmConfig.isAlarmSoundOn = stmt->ValueInt(7);
		mAlarmConfig.alarmSoundId = stmt->ValueInt(8);
		mAlarmConfig.defutAlarmSoundSec = stmt->ValueInt(9);
		mAlarmConfig.alarmSoundSec = stmt->ValueInt(10);
	}
	else {
		Print("Load system config error: Find none db stmt");
	}
}



void CSystemConfig::SetAlarmConfig(SystemAlarmConfig* pConfig, UINT16 mask)
{
	if (mask & SYS_CONFIG_AL) {
		mAlarmConfig.isAlarmLightOn  = pConfig->isAlarmLightOn;
	}

	if (mask & SYS_CONFIG_AS) {
		mAlarmConfig.isAlarmSoundOn  = pConfig->isAlarmSoundOn;
	}

	if (mask & SYS_CONFIG_ASID) {
		mAlarmConfig.alarmSoundId  = pConfig->alarmSoundId;
	}

	if (mask & SYS_CONFIG_ASDFTSEC) {
		mAlarmConfig.defutAlarmSoundSec  = pConfig->defutAlarmSoundSec;
	}

	if (mask & SYS_CONFIG_ASSEC) {
		mAlarmConfig.alarmSoundSec  = pConfig->alarmSoundSec;
	}	
}



void CSystemConfig::SetAutoWatchConfig(SystemAutoWatchConfig* pConfig, UINT16 mask)
{
	if (mask & SYS_CONFIG_AW) {
		mAutoWatchConfig.isAutoWatchOn  = pConfig->isAutoWatchOn;
	}

	if (mask & SYS_CONFIG_AWBT) {
		mAutoWatchConfig.autoWatchBeginTime  = pConfig->autoWatchBeginTime;
	}

	if (mask & SYS_CONFIG_AWET) {
		mAutoWatchConfig.autoWatchEndTime  = pConfig->autoWatchEndTime;
	}
}



void CSystemConfig::SetBoatName(std::string& name)
{
	mBoatName  = name;
}



void CSystemConfig::SetBrightness(UINT16 brt)
{
	mBrtness  = brt;
}



void CSystemConfig::SetVolumn(UINT16 vol)
{
	mVol   = vol;
}