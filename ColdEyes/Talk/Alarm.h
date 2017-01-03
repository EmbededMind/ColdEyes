#pragma once
#include "stdafx.h"
#include "Talk\IState.h"

class CTalk;
class CAlarm:public IState
{
public:
	CAlarm(CTalk *talk);
	~CAlarm();

	CTalk *mTalk;

	void HostTalk(CCamera *pDev);

	void CameraWantTalk(CCamera *pDev);

	void Stop();
	void ReStop();

	void TurnOnLED();
	void ReTurnOnLED();

	void TurnOffLED();
	void ReTurnOffLED();

	void SetVolume(CCamera *pDev, int volume);
	void ReSetVolume(CCamera *pDev, int volume);
};

