#include "stdafx.h"
#include "Alarm.h"
#include "Talk\Talk.h"

CAlarm::CAlarm(CTalk *talk)
{
	mTalk = talk;
}


CAlarm::~CAlarm()
{
}

void CAlarm::HostTalk(CCamera * pDev)
{
	SetEvent(mTalk->mStopAlarmEvent);
}

void CAlarm::CameraWantTalk(CCamera * pDev)
{
	SetEvent(mTalk->mStopAlarmEvent);
}

void CAlarm::Stop()
{
	SetEvent(mTalk->mStopAlarmEvent);
}

void CAlarm::ReStop()
{
	SetEvent(mTalk->mReStopAlarmEvent);
}

void CAlarm::TurnOnLED()
{
	SetEvent(mTalk->mTurnOnLEDEvent);
}

void CAlarm::ReTurnOnLED()
{
	SetEvent(mTalk->mReTurnOnLEDEvent);
}

void CAlarm::TurnOffLED()
{
	SetEvent(mTalk->mTurnOffLEDEvent);
}

void CAlarm::ReTurnOffLED()
{
	SetEvent(mTalk->mReTurnOffLEDEvent);
}

void CAlarm::SetVolume(CCamera * pDev, int volume)
{
	SetEvent(mTalk->mSetVolumeEvent);
}

void CAlarm::ReSetVolume(CCamera * pDev, int volume)
{
	SetEvent(mTalk->mReSetVolumeEvent);
}
