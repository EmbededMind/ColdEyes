#include "stdafx.h"
#include "Talk\Free.h"
#include "Talk\Talk.h"

CFree::CFree(CTalk *talk)
{
	this->mTalk = talk;
}


CFree::~CFree()
{
}

void CFree::HostTalk(CCamera * pDev)
{
	SetEvent(mTalk->mHostTalkEvent);
}

void CFree::ReHostTalk(CCamera * pDev)
{
	SetEvent(mTalk->mReHostTalkEvent);
}

void CFree::CameraWantTalk(CCamera * pDev)
{
	SetEvent(mTalk->mCameraWantTalkEvent);
}

void CFree::CameraCanTalk(CCamera * pDev)
{
	SetEvent(mTalk->mCameraCanTalkEvent);
}

void CFree::Alarm(CCamera * pDev)
{
	SetEvent(mTalk->mAlarmEvent);
}

void CFree::ReAlarm(CCamera * pDev)
{
	SetEvent(mTalk->mReAlarmEvent);
}

void CFree::TurnOnLED()
{
	SetEvent(mTalk->mTurnOnLEDEvent);
}

void CFree::ReTurnOnLED()
{
	SetEvent(mTalk->mReTurnOnLEDEvent);
}

void CFree::TurnOffLED()
{
	SetEvent(mTalk->mTurnOffLEDEvent);
}

void CFree::ReTurnOffLED()
{
	SetEvent(mTalk->mReTurnOffLEDEvent);
}

void CFree::SetVolume(CCamera * pDev, int volume)
{
	SetEvent(mTalk->mSetVolumeEvent);
}

void CFree::ReSetVolume(CCamera * pDev, int volume)
{
	SetEvent(mTalk->mReSetVolumeEvent);
}

