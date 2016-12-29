#include "stdafx.h"
#include "AlphaMarkWnd.h"

CAlphaMarkWnd::CAlphaMarkWnd()
{
}

CAlphaMarkWnd::CAlphaMarkWnd(CDuiString skinName)
{
	if (skinName)
		mSkinFileName = skinName;
}

CAlphaMarkWnd::~CAlphaMarkWnd()
{
}

LPCTSTR CAlphaMarkWnd::GetWindowClassName() const
{
	return _T("AlphaMarkWnd");
}

CDuiString CAlphaMarkWnd::GetSkinFile()
{
	if (mSkinFileName)
		return mSkinFileName;
}


LRESULT CAlphaMarkWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	//Print("AlpWnd msg:%d", uMsg);
	//CDuiString PlayText;
	//switch (uMsg) {
	//case USER_MSG_PLAY_PLAY:
	//	ShowWindow(false);
	//	break;
	//	
	//case USER_MSG_PLAY_SLOW:
	//	wParam = pow(2, wParam);
	//	PlayText.Format(_T("X%d"), wParam);
	//	pBt_fast->SetVisible(false);
	//	pBt_slow->SetVisible(true);
	//	pBt_slow->SetText(PlayText);
	//	break;

	//case USER_MSG_PLAY_FAST:
	//	wParam = pow(2, wParam);
	//	PlayText.Format(_T("X%d"), wParam);
	//	pBt_slow->SetVisible(false);
	//	pBt_fast->SetVisible(true);
	//	pBt_fast->SetText(PlayText);
	//	break;

	//case WM_SETFOCUS:		
	//	SetFocus(pPlayerWall->GetHWND());
	//	break;
	//}	 
	bHandled = FALSE;
	return 0;
}

void CAlphaMarkWnd::Notify(TNotifyUI & msg)
{
}

void CAlphaMarkWnd::InitWindow()
{
	m_pm.SetDPI(mDpi);
	pBt_fast = static_cast<CButtonUI*>(m_pm.FindControl(_T("bt_fast")));
	pBt_slow = static_cast<CButtonUI*>(m_pm.FindControl(_T("bt_slow")));
}

void CAlphaMarkWnd::SetPlayerWnd(CPlayerWallWnd *pWnd)
{
	pPlayerWall = pWnd;
}

void CAlphaMarkWnd::SetDpi(int dpi)
{
	mDpi = dpi;
}
