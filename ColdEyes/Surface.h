#pragma once
#include "stdafx.h"
#include "SurfaceFrame.h"

#include "Device\Port.h"

#include "NetSdk\H264Play.h"

class CSurface : public CWnd
{
	DECLARE_DYNAMIC(CSurface)

public:
	CSurface();
	virtual ~CSurface();


public:
	void            BindPort(CPort* pPort);
	bool            IsRealPlaying();
	long            GetPlayPort();
	void            OnCameraLogin();
	void            SetPos();
	void            SetPos(CRect& r);

protected:
	H264_DVR_CLIENTINFO mClientInfo;
	bool                mHaveConnectRealPlay;
	bool                mIsLargeMode;
	bool                mIsRealPlaying;
	CPort*              mPort;
	CSurfaceFrame       mFrame;
	OSD_INFO_TXT        mOsdText;
	int                 mOsdTextIndex;
	long                mPlayPort;
	CRect               mSplitPos;

	long                mRealPlayHandle;

	bool            ConnectRealPlay();
	bool            DisconnectRealPlay();



	BOOL            RegisterWindowClass(HINSTANCE hInstance = NULL);

	bool            StartRealPlay();
	bool            StopRealPlay();
};