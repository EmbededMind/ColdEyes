#include "stdafx.h"
#include "Talk.h"


CTalk::CTalk()
{
	mFreeState = new CFree(this);
	mHostTalkState = new CHostTalk(this);
	mCameraTalkState = new CCameraTalk(this);
	mAlarmState = new CAlarm(this);
}


CTalk::~CTalk()
{
}

bool CTalk::Init()
{
	if (mStopThreadEvent != NULL)
		ResetEvent(mStopThreadEvent);
	else
		mStopThreadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mReStopAlarmEvent != NULL)
		ResetEvent(mReStopAlarmEvent);
	else
		mReStopAlarmEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mReStopTalkEvent != NULL)
		ResetEvent(mReStopTalkEvent);
	else
		mReStopTalkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mReHostTalkEvent != NULL)
		ResetEvent(mReHostTalkEvent);
	else
		mReHostTalkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mCameraWantTalkEvent != NULL)
		ResetEvent(mCameraWantTalkEvent);
	else
		mCameraWantTalkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mReCameraTalkEvent != NULL)
		ResetEvent(mReCameraTalkEvent);
	else
		mReCameraTalkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mReAlarmEvent != NULL)
		ResetEvent(mReAlarmEvent);
	else
		mReAlarmEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mReTurnOnLEDEvent != NULL)
		ResetEvent(mReTurnOnLEDEvent);
	else
		mReTurnOnLEDEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mReTurnOffLEDEvent != NULL)
		ResetEvent(mReTurnOffLEDEvent);
	else
		mReTurnOffLEDEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mReSetVolumeEvent != NULL)
		ResetEvent(mReSetVolumeEvent);
	else
		mReSetVolumeEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mStopAlarmEvent != NULL)
		ResetEvent(mStopAlarmEvent);
	else
		mStopAlarmEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mStopTalkEvent != NULL)
		ResetEvent(mStopTalkEvent);
	else
		mStopTalkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mHostTalkEvent != NULL)
		ResetEvent(mHostTalkEvent);
	else
		mHostTalkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mCameraCanTalkEvent != NULL)
		ResetEvent(mCameraCanTalkEvent);
	else
		mCameraCanTalkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mCameraTalkEvent != NULL)
		ResetEvent(mCameraTalkEvent);
	else
		mCameraTalkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mAlarmEvent != NULL)
		ResetEvent(mAlarmEvent);
	else
		mAlarmEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mTurnOffLEDEvent != NULL)
		ResetEvent(mTurnOffLEDEvent);
	else
		mTurnOffLEDEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mTurnOnLEDEvent != NULL)
		ResetEvent(mTurnOnLEDEvent);
	else
		mTurnOnLEDEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mSetVolumeEvent != NULL)
		ResetEvent(mSetVolumeEvent);
	else
		mSetVolumeEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mPostTalkEvent != NULL)
		ResetEvent(mPostTalkEvent);
	else
		mPostTalkEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	mEventArray[STOP_THREAD] = mStopThreadEvent;
	mEventArray[RE_STOP_ALARM] = mReStopAlarmEvent;
	mEventArray[RE_STOP_TALK] = mReStopTalkEvent;
	mEventArray[RE_HOST_TALK] = mReHostTalkEvent;
	mEventArray[CAMERA_WANT_TALK] = mCameraWantTalkEvent;
	mEventArray[RE_CAMERA_TALK] = mReCameraTalkEvent;
	mEventArray[RE_ALARM] = mReAlarmEvent;
	mEventArray[RE_TURNON_LED] = mReTurnOnLEDEvent;
	mEventArray[RE_TURNOFF_LED] = mReTurnOffLEDEvent;
	mEventArray[RE_SET_VOLUME] = mReSetVolumeEvent;
	mEventArray[STOP_ALARM] = mStopAlarmEvent;
	mEventArray[STOP_TALK] = mStopTalkEvent;
	mEventArray[HOST_TALK] = mHostTalkEvent;
	mEventArray[CAMERA_CAN_TALK] = mCameraCanTalkEvent;
	mEventArray[CAMERA_TALK] = mCameraTalkEvent;
	mEventArray[ALARM] = mAlarmEvent;
	mEventArray[TURNOFF_LED] = mTurnOffLEDEvent;
	mEventArray[TURNON_LED] = mTurnOnLEDEvent;
	mEventArray[SET_VOLUME] = mSetVolumeEvent;
	mEventArray[POST_TALK] = mPostTalkEvent;
	return false;
}

bool CTalk::StartThread()
{
	if (!(mThread = AfxBeginThread(TalkThread, this)))
		return false;
	return true;
}

UINT CTalk::TalkThread(LPVOID pParam)
{
	CTalk *pThis = (CTalk*)pParam;
	DWORD Event = 0;
	for (;;)
	{
		Event = WaitForMultipleObjects(EVENTNUM, pThis->mEventArray, FALSE, INFINITE);
		switch (Event)
		{
		case STOP_THREAD:
			AfxEndThread(10);
			break;

		case RE_STOP_ALARM:
			//关闭报警播放
			break;

		case RE_STOP_TALK:
			//关闭语音对讲
			H264_DVR_StopVoiceCom(pThis->mTalkHandle);
			break;

		case RE_HOST_TALK:
			//打开语音对讲
			break;

		case CAMERA_WANT_TALK:
			//有摄像头要讲话
			break;

		case RE_CAMERA_TALK:
			//让摄像头讲话
			break;

		case RE_ALARM:
			//打开语音 播放报警音
			break;

		case RE_TURNON_LED:
			//返回LED打开结果
			break;

		case RE_TURNOFF_LED:
			//返回LED关闭结果
			break;

		case RE_SET_VOLUME:
			//返回音量设置结果
			break;

		case STOP_ALARM:
			//停止报警
			break;

		case STOP_TALK:
			//停止讲话
			break;

		case HOST_TALK:
			//主机讲话
			break;

		case CAMERA_CAN_TALK:
			//摄像头要讲话，允许讲话
			break;

		case CAMERA_TALK:
			//让摄像头讲话
			break;

		case ALARM:
			//报警开始
			break;

		case TURNOFF_LED:
			//关闭LED
			break;

		case TURNON_LED:
			//打开LED
			break;

		case SET_VOLUME:
			//设置音量
			break;

		case POST_TALK:
			//对讲过程中，摄像头请求讲话
			break;
		default:
			break;
		}
	}
	return 0;
}

void CTalk::HandleData(UINT8 * pData, size_t length)
{
	UINT8 cmd = pData[3];
	memcpy(ComData[cmd], pData, length);
}

void CTalk::SetFreeState()
{
	mOldState = mState;
	mState = mFreeState;
}

void CTalk::SetHostTalkState()
{
	mOldState = mState;
	mState = mHostTalkState;
}

void CTalk::SetCameraTalkState()
{
	mOldState = mState;
	mState = mCameraTalkState;
}

void CTalk::SetAlarmState()
{
	mOldState = mState;
	mState = mAlarmState;
}

void CTalk::RecoverState()
{
	IState *tmp;
	tmp = mOldState;
	mOldState = mState;
	mState = tmp;
}

IState * CTalk::GetFreeState()
{
	return mFreeState;
}

IState * CTalk::GetHostTalkState()
{
	return mHostTalkState;
}

IState * CTalk::GetCameraTalkState()
{
	return mCameraTalkState;
}

IState * CTalk::GetAlarmState()
{
	return mAlarmState;
}

//state CTalk::GetCurrentStateByenum()
//{
//	if (mState == mFreeState)
//		return Free;
//	if (mState == mHostTalkState)
//		return HostTalk;
//	if (mState == mCameraTalkState)
//		return CameraTalk;
//	if (mState == mAlarmState)
//		return Alarm;
//}

IState * CTalk::GetCurrentState()
{
	return mState;
}

void CTalk::HostTalk(CCamera * pDev)
{
	
	mState->HostTalk(pDev);
}

void CTalk::ReHostTalk(CCamera * pDev)
{
}

void CTalk::CameraTalk(CCamera * pDev)
{
}

void CTalk::ReCameraTalk(CCamera * pDev)
{
}

void CTalk::CameraWantTalk(CCamera * pDev)
{
}

void CTalk::CameraCanTalk(CCamera * pDev)
{
}

void CTalk::Alarm(CCamera * pDev)
{
}

void CTalk::ReAlarm(CCamera * pDev)
{
}

void CTalk::Stop(CCamera * pDev)
{
}

void CTalk::ReStop(CCamera * pDev)
{
}

void CTalk::TurnOnLED()
{
}

void CTalk::ReTurnOnLED()
{
}

void CTalk::TurnOffLED()
{
}

void CTalk::ReTurnOffLED()
{
}

void CTalk::SetVolume(CCamera * pDev, int volume)
{
}

void CTalk::ReSetVolume(CCamera * pDev, int volume)
{
}

void CTalk::SetRouter(CRouter * p)
{
	this->mpRouter = p;
}
