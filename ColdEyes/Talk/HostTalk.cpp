#include "stdafx.h"
#include "HostTalk.h"
#include "Talk\Talk.h"

CHostTalk::CHostTalk(CTalk *talk)
{
	mTalk = talk;
}


CHostTalk::~CHostTalk()
{
}


void CHostTalk::CameraTalk(CCamera * pDev)
{
	SetEvent(mTalk->mCameraTalkEvent);
}

void CHostTalk::ReCameraTalk(CCamera * pDev)
{
	SetEvent(mTalk->mReCameraTalkEvent);
}

void CHostTalk::CameraWantTalk(CCamera * pDev)
{
	SetEvent(mTalk->mPostTalkEvent);
}

void CHostTalk::Stop()
{
	SetEvent(mTalk->mStopTalkEvent);
}

void CHostTalk::ReStop()
{
	SetEvent(mTalk->mReStopTalkEvent);
}

void CHostTalk::TurnOnLED()
{
	SetEvent(mTalk->mTurnOnLEDEvent);
}

void CHostTalk::ReTurnOnLED()
{
	SetEvent(mTalk->mReTurnOnLEDEvent);
}

void CHostTalk::TurnOffLED()
{
	SetEvent(mTalk->mTurnOffLEDEvent);
}

void CHostTalk::ReTurnOffLED()
{
	SetEvent(mTalk->mReTurnOffLEDEvent);
}

void CHostTalk::SetVolume(CCamera * pDev, int volume)
{
	SetEvent(mTalk->mSetVolumeEvent);
}

void CHostTalk::ReSetVolume(CCamera * pDev, int volume)
{
	SetEvent(mTalk->mReSetVolumeEvent);
}
