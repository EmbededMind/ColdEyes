#pragma once
#include "stdafx.h"
#include "Talk\IState.h"

class CTalk;
class CFree :public IState
{
public:
	CFree(CTalk *talk);
	~CFree();

	CTalk *mTalk;

	void HostTalk(CCamera *pDev);
	void ReHostTalk(CCamera *pDev);

	void CameraWantTalk(CCamera *pDev);
	void CameraCanTalk(CCamera *pDev);

	void Alarm(CCamera *pDev);
	void ReAlarm(CCamera *pDev);

	void TurnOnLED();
	void ReTurnOnLED();

	void TurnOffLED();
	void ReTurnOffLED();

	void SetVolume(CCamera *pDev, int volume);
	void ReSetVolume(CCamera *pDev, int volume);
};

