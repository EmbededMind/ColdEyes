#pragma once
#include "stdafx.h"
#include "Talk\IState.h"

class CTalk;
class CCameraTalk:public IState
{
public:
	CCameraTalk(CTalk *talk);
	~CCameraTalk();

	CTalk *mTalk;

	void HostTalk(CCamera *pDev);
	void ReHostTalk(CCamera *pDev);

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

