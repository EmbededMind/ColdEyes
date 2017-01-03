#pragma once
#include "Device\Camera.h"
class IState
{
public:
	IState() {};
	~IState() {};
	virtual void HostTalk(CCamera *pDev) {};
	virtual void ReHostTalk(CCamera *pDev) {};

	virtual void CameraTalk(CCamera *pDev) {};
	virtual void ReCameraTalk(CCamera *pDev) {};

	virtual void CameraWantTalk(CCamera *pDev) {};
	virtual void CameraCanTalk(CCamera *pDev) {};

	virtual void Alarm(CCamera *pDev) {};
	virtual void ReAlarm(CCamera *pDev) {};

	virtual void Stop() {};
	virtual void ReStop() {};

	virtual void TurnOnLED() {};
	virtual void ReTurnOnLED() {};

	virtual void TurnOffLED() {};
	virtual void ReTurnOffLED() {};

	virtual void SetVolume(CCamera *pDev, int volume) {};
	virtual void ReSetVolume(CCamera *pDev, int volume) {};
};

