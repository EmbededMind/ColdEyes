#pragma once

#include "DuiLib\UIlib.h"
#include "NetSdk\H264Play.h"

class CPlayerWallWnd;

using namespace std;
using namespace DuiLib;

class CAlphaMarkWnd
	:public WindowImplBase {

public:
	CAlphaMarkWnd();
	CAlphaMarkWnd(CDuiString);
	~CAlphaMarkWnd();

	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void Notify(TNotifyUI& msg);
	void InitWindow();
	void SetPlayerWnd(CPlayerWallWnd*);
	void SetDpi(int dpi);
private:
	CPlayerWallWnd *pPlayerWall;
	CDuiString mSkinFileName;

	CButtonUI* pBt_fast;
	CButtonUI* pBt_slow;
	int mDpi;
};