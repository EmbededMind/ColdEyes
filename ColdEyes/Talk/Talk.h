#pragma once
#include "stdafx.h"
#include "Talk\IState.h"
#include "Pattern\IDataHandler.h"
#include "Talk\Free.h"
#include "Talk\HostTalk.h"
#include "Talk\CameraTalk.h"
#include "Talk\Alarm.h"
#include "Com\Router.h"

#define EVENTNUM 20
#define STOP_THREAD 0
#define RE_STOP_ALARM 1
#define RE_STOP_TALK 2
#define RE_HOST_TALK 3
#define CAMERA_WANT_TALK 4
#define RE_CAMERA_TALK 5
#define RE_ALARM 6
#define RE_TURNON_LED 7
#define RE_TURNOFF_LED 8
#define RE_SET_VOLUME 9
#define STOP_ALARM 10
#define STOP_TALK 11
#define HOST_TALK 12
#define CAMERA_CAN_TALK 13
#define CAMERA_TALK 14
#define ALARM 15
#define TURNOFF_LED 16
#define TURNON_LED 17
#define SET_VOLUME 18
#define POST_TALK 19

//enum state {
//	Free = 0,
//	HostTalk,
//	CameraTalk,
//	Alarm,
//};
class CTalk :public IState, public IDataHandler
{
public:
	CTalk();
	~CTalk();
	static CTalk* GetInstance()
	{
		static CTalk instance;
		return &instance;
	}
	bool Init();
	bool StartThread();
public:
	HANDLE mStopThreadEvent;
	HANDLE mHostTalkEvent;
	HANDLE mReHostTalkEvent;
	HANDLE mCameraTalkEvent;
	HANDLE mReCameraTalkEvent;
	HANDLE mCameraWantTalkEvent;
	HANDLE mCameraCanTalkEvent;
	HANDLE mAlarmEvent;
	HANDLE mReAlarmEvent;
	HANDLE mStopTalkEvent;
	HANDLE mReStopTalkEvent;
	HANDLE mStopAlarmEvent;
	HANDLE mReStopAlarmEvent;
	HANDLE mTurnOnLEDEvent;
	HANDLE mReTurnOnLEDEvent;
	HANDLE mTurnOffLEDEvent;
	HANDLE mReTurnOffLEDEvent;
	HANDLE mSetVolumeEvent;
	HANDLE mReSetVolumeEvent;
	HANDLE mPostTalkEvent;
private:
	CWinThread* mThread;
	static UINT TalkThread(LPVOID pParam);
	IState *mFreeState;
	IState *mHostTalkState;
	IState *mCameraTalkState;
	IState *mAlarmState;
	IState *mState;
	IState *mOldState;

	UINT8 ComData[EVENTNUM][17];
	HANDLE mEventArray[EVENTNUM];
	
	CRouter *mpRouter;
	long mTalkHandle;
	CCamera *pTalkDev;
public:
	void HandleData(UINT8* pData, size_t length);
	void SetFreeState();
	void SetHostTalkState();
	void SetCameraTalkState();
	void SetAlarmState();
	void RecoverState();

	IState *GetFreeState();
	IState *GetHostTalkState();
	IState *GetCameraTalkState();
	IState *GetAlarmState();

	//state GetCurrentStateByenum();
	IState* GetCurrentState();

	void HostTalk(CCamera *pDev);
	void ReHostTalk(CCamera *pDev);

	void CameraTalk(CCamera *pDev);
	void ReCameraTalk(CCamera *pDev);

	void CameraWantTalk(CCamera *pDev);
	void CameraCanTalk(CCamera *pDev);

	void Alarm(CCamera *pDev);
	void ReAlarm(CCamera *pDev);

	void Stop(CCamera *pDev);
	void ReStop(CCamera *pDev);

	void TurnOnLED();
	void ReTurnOnLED();

	void TurnOffLED();
	void ReTurnOffLED();

	void SetVolume(CCamera *pDev, int volume);
	void ReSetVolume(CCamera *pDev, int volume);

	void SetRouter(CRouter *p);
};

