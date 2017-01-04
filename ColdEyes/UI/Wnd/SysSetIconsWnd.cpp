#include "stdafx.h"
#include "SysSetIconsWnd.h"

CSysSetIconsWnd::CSysSetIconsWnd()
{
}

CSysSetIconsWnd::CSysSetIconsWnd(CDuiString skinName)
{
	if (skinName)
		mSkinFileName = skinName;
}

CSysSetIconsWnd::~CSysSetIconsWnd()
{
}

LPCTSTR CSysSetIconsWnd::GetWindowClassName() const
{
	return _T("SysSetWnd");
}

CDuiString CSysSetIconsWnd::GetSkinFile()
{
	if (mSkinFileName)
		return mSkinFileName;
}


LRESULT CSysSetIconsWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	switch(uMsg){
	case WM_WINDOWPOSCHANGED:
		if (IsWindowVisible(m_hWnd)) {
			::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		break;

	case WM_SETFOCUS:
		if(pMainWnd)
			pMainWnd->SetFocus();
		break;

	case WM_SHOWWINDOW:
		mshowTime = 2;
		SetTimer(m_hWnd, 1, 1000, NULL);
		break;

	case SWP_HIDEWINDOW:
		mshowTime = 2;
		break;

	case USER_MSG_SYS_VOLUME:
		pMainWnd = (CWnd*)lParam;
		if (!IsWindowVisible(m_hWnd)) {
			ShowWindow(true);
		}
		pVolume->SetVisible(true);
		pLight->SetVisible(false);
		pProgress->SetValue(wParam*10);
		mshowTime = 1;
		break;
		
	case USER_MSG_SYS_LIGHT:
		pVolume->SetVisible(false);
		pLight->SetVisible(true);
		mshowTime = 1;
		break;

	case WM_TIMER:
		if (!mshowTime) {
			ShowWindow(false);
			KillTimer(m_hWnd, 1);
		}
		else mshowTime--;
		break;
	}
	bHandled = FALSE;
	return 0;
}

void CSysSetIconsWnd::Notify(TNotifyUI & msg)
{
}

void CSysSetIconsWnd::InitWindow()
{
	m_pm.SetDPI(mDpi);
	pVolume = static_cast<CLabelUI*>(m_pm.FindControl(_T("volume")));
	pLight = static_cast<CLabelUI*>(m_pm.FindControl(_T("light")));
	pProgress = static_cast<CProgressUI*>(m_pm.FindControl(_T("value")));
}



void CSysSetIconsWnd::SetDpi(int dpi)
{
	mDpi = dpi;
}
