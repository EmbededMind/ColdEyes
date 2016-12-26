#include "stdafx.h"
#include "PlayerWallWnd.h"
#include <list>

CPlayerWallWnd::CPlayerWallWnd()
{
}

CPlayerWallWnd::CPlayerWallWnd(CDuiString skinName)
{
	mSkinFileName = skinName;
}

CPlayerWallWnd::~CPlayerWallWnd()
{
}

LPCTSTR CPlayerWallWnd::GetWindowClassName() const
{
	return _T("PlayerWallWnd");
}

CDuiString CPlayerWallWnd::GetSkinFile()
{
	return mSkinFileName;
}

LRESULT CPlayerWallWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{

	bHandled = FALSE;
	return 0;
}

void CPlayerWallWnd::InitWindow()
{
	pSlow = static_cast<CButtonUI*>(m_pm.FindControl(_T("bt_slow")));
	pPlay = static_cast<CButtonUI*>(m_pm.FindControl(_T("bt_play")));
	pFast = static_cast<CButtonUI*>(m_pm.FindControl(_T("bt_fast")));
	pSlider = static_cast<CSliderUI*>(m_pm.FindControl(_T("progress")));
	pBeginTime = static_cast<CLabelUI*>(m_pm.FindControl(_T("time_begin")));
	pEndTime = static_cast<CLabelUI*>(m_pm.FindControl(_T("time_end")));

	if (!pVPlayerWnd) {
		pVPlayerWnd = new CVPlayer(_T("vplayer.xml"));
		pVPlayerWnd->Create(m_hWnd, _T("VPlayer"), UI_WNDSTYLE_CHILD, WS_EX_WINDOWEDGE, { 0,0,0,0 });
	
	}

	if (!pMarkWnd) {
		pMarkWnd = new CAlphaMarkWnd(_T("player_alpha_mark.xml"));
		pMarkWnd->ShowWindow(SW_HIDE);
	}
}
