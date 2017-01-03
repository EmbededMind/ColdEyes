#include "stdafx.h"
#include "Talk\CameraTalk.h"
#include "Talk\Talk.h"
CCameraTalk::CCameraTalk(CTalk *talk)
{
	this->mTalk = talk;
}


CCameraTalk::~CCameraTalk()
{
}

void CCameraTalk::HostTalk(CCamera * pDev)
{
	SetEvent(mTalk->mHostTalkEvent);
}

void CCameraTalk::ReHostTalk(CCamera * pDev)
{
	SetEvent(mTalk->mReHostTalkEvent);
}

void CCameraTalk::CameraWantTalk(CCamera * pDev)
{
	SetEvent(mTalk->mPostTalkEvent);
}

void CCameraTalk::Stop()
{
	SetEvent(mTalk->mStopTalkEvent);
}

void CCameraTalk::ReStop()
{
	SetEvent(mTalk->mReStopTalkEvent);
}

void CCameraTalk::TurnOnLED()
{
	SetEvent(mTalk->mTurnOnLEDEvent);
}

void CCameraTalk::ReTurnOnLED()
{
	SetEvent(mTalk->mReTurnOnLEDEvent);
}

void CCameraTalk::TurnOffLED()
{
	SetEvent(mTalk->mTurnOffLEDEvent);
}

void CCameraTalk::ReTurnOffLED()
{
	SetEvent(mTalk->mReTurnOffLEDEvent);
}

void CCameraTalk::SetVolume(CCamera * pDev, int volume)
{
	SetEvent(mTalk->mSetVolumeEvent);
}

void CCameraTalk::ReSetVolume(CCamera * pDev, int volume)
{
	SetEvent(mTalk->mReSetVolumeEvent);
}
