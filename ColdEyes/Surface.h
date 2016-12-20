#pragma once
#include "stdafx.h"
#include "SurfaceFrame.h"

#include "Device\Port.h"

class CSurface : public CWnd
{
	DECLARE_DYNAMIC(CSurface)

public:
	CSurface();
	virtual ~CSurface();


public:
	void            BindPort(CPort* pPort);
	void            SetPos();
	void            SetPos(CRect& r);

protected:
	CSurfaceFrame   mFrame;
	bool            mIsLargeMode;
	CRect           mSplitPos;

	BOOL            RegisterWindowClass(HINSTANCE hInstance = NULL);

private:
	CPort*          mPort;

};