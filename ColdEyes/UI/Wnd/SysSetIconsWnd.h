#pragma once

#include "DuiLib\UIlib.h"


using namespace DuiLib;

class CSysSetIconsWnd
	:public WindowImplBase {

public:
	CSysSetIconsWnd();
	CSysSetIconsWnd(CDuiString);
	~CSysSetIconsWnd();

	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void Notify(TNotifyUI& msg);
	void InitWindow();
	void SetDpi(int dpi);
private:
	CDuiString mSkinFileName;

	CLabelUI* pVolume;
	CLabelUI* pLight;
	CProgressUI* pProgress;
	int Value;
	int mshowTime;
	int mDpi;
	CWnd* pMainWnd;
};