#pragma once
#include "stdafx.h"
#include "Talk\IState.h"

class CTalk;
class CHostTalk:public IState
{
public:
	CHostTalk(CTalk *talk);
	~CHostTalk();

	CTalk *mTalk;

	void CameraTalk(CCamera *pDev);
	void ReCameraTalk(CCamera *pDev);

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

