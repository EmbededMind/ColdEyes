#include "stdafx.h"

#include "Config\SystemConfig.h"
#include "Database\DBHelper.h"

CSystemConfig::CSystemConfig()
{
	mBoatName        = DEFUT_SYSCONFIG_BOATNAME;
	mBrtness         = DEFUT_SYSCONFIG_BRTNESS;
	mVol             = DEFUT_SYSCONFIG_VOL;
	mAlIsOn          = DEFUT_SYSCONFIG_AL;
	mAwIsOn          = DEFUT_SYSCONFIG_AW;
	mAwBeginTime     = DEFUT_SYSCONFIG_AWBT;
	mAwEndTime       = DEFUT_SYSCONFIG_AWET;
	mAsIsOn          = DEFUT_SYSCONFIG_AS;
	mAsId            = DEFUT_SYSCONFIG_ASID;
	mAsDefaultSec    = DEFUT_SYSCONFIG_ASSEC;
	mAsSec           = 0;
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
					mAwIsOn, mAwBeginTime, mAwEndTime);
	helper.Update("sys_config", formatValues);
}



void CSystemConfig::CommitAlarmUpdate()
{
	CDBHelper& helper  = CDBHelper::GetInstance();

	char formatValues[100];
	sprintf_s(formatValues, "alarm_light = %d, alarm_sound = %d, as_id = %d, as_defut_sec = %d,as_sec = %d",
				mAlIsOn, mAsIsOn, mAsId, mAsDefaultSec, mAsSec);
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