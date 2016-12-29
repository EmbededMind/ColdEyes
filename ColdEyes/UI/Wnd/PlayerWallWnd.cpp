#include "stdafx.h"
#include "PlayerWallWnd.h"
#include <list>


void __stdcall EOFCallBack(LONG mPort, LONG nUser)
{
	((CPlayerWallWnd *)nUser)->StopPlay();
}

CPlayerWallWnd::CPlayerWallWnd()
	:m_nRate(0),
	timeCnt(999)
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
	switch (uMsg) {
	case WM_TIMER:
		OnTimer(uMsg, wParam, lParam, bHandled);
		break;
	}
	bHandled = FALSE;
	return 0;
}

LRESULT CPlayerWallWnd::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	switch (wParam) {
	case VK_LEFT:
		OnBack();
		break;

	case VK_RIGHT:
		OnFast();
		break;

	case VK_RETURN:
		OnPlay();
		break;

	case VK_UP:
		return true;
		break;

	case VK_BACK:
		//ClosePlayer();
		break;

	//case VK_APPS:
	//	Print("Print Vk_apps");
	//	return true;
	//	pMenuWnd->FocusedReset();
	//	ClosePlayer();
	//	break;
	}

	return LRESULT();
}


void CPlayerWallWnd::InitWindow()
{
	m_pm.SetDPI(((CColdEyesDlg*)AfxGetMainWnd())->mMenu->GetDpi());
	pSlow = static_cast<CButtonUI*>(m_pm.FindControl(_T("bt_slow")));
	pPlay = static_cast<CButtonUI*>(m_pm.FindControl(_T("bt_play")));
	pFast = static_cast<CButtonUI*>(m_pm.FindControl(_T("bt_fast")));
	pSlider = static_cast<CSliderUI*>(m_pm.FindControl(_T("progress")));
	pBeginTime = static_cast<CLabelUI*>(m_pm.FindControl(_T("time_begin")));
	pEndTime = static_cast<CLabelUI*>(m_pm.FindControl(_T("time_end")));

	if (!pVPlayerWnd) {
		pVPlayerWnd = new CVPlayer(_T("vplayer.xml"));
		pVPlayerWnd->SetDpi(((CColdEyesDlg*)AfxGetMainWnd())->mMenu->GetDpi());
		pVPlayerWnd->Create(m_hWnd, _T("VPlayer"), UI_WNDSTYLE_CHILD, WS_EX_WINDOWEDGE, { 0,0,0,0 });
	}

	PreparePlay();
	//if (!pMarkWnd) {
	//	pMarkWnd = new CAlphaMarkWnd(_T("player_alpha_mark.xml"));
	//	pMarkWnd->ShowWindow(SW_HIDE);
	//}

	DWORD Version;
	Version =  H264_PLAY_GetSdkVersion();
	Print("version:%ld,%x",Version,Version);
}

LRESULT CPlayerWallWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	switch (wParam) {
	case 1:
		{
			DWORD PlayTime;
			int mProgress = 100 * H264_PLAY_GetPlayPos(m_Port);
			PlayTime = H264_PLAY_GetPlayedTime(m_Port);
			CDuiString sTime;
			sTime.Format(_T("%02d:%02d:%02d"), PlayTime / 3600, PlayTime / 60, PlayTime % 60);
			pBeginTime->SetText(sTime);
			pSlider->SetValue(mProgress);


			PlayTime = H264_PLAY_GetPlayedTimeEx(m_Port);
			Print("playtime:%ld",PlayTime);
			break;
		}
	//---------------------------------
	case 2:
		//int res;
		//res = H264_PLAY_PrevFrame(m_Port);
		//Print("err:%d,port:%d", res,m_Port);

		DWORD PlayTime ;
		PlayTime = H264_PLAY_GetPlayedTimeEx(m_Port);

		if (PlayTime > 1000) {
			PlayTime -= 1000;
			H264_PLAY_SetPlayedTimeEx(m_Port, PlayTime);
			//H264_PLAY_RefreshPlay(m_Port);
		}
		else
			KillTimer(m_hWnd,2);	
		
		timeCnt++;
		if (timeCnt == 1000) {
			timeCnt = 0;
			PlayTime = H264_PLAY_GetPlayedTimeEx(m_Port);
			Print("playtime:%ld",PlayTime);
		}
		break;
	}

	bHandled = TRUE;
	return 0;
}

void CPlayerWallWnd::InitPlayOptionImage()
{
	sPlayFocusedImg = _T("file='image/play_focused.png'");
	sPlayNoFocusImg = _T("file='image/play.png'");
	sStopFocusedImg = _T("file='image/pause_focused.png'");
	sStopNoFocusImg = _T("file='image/pause.png'");
}



void CPlayerWallWnd::PreparePlay()
{
	H264_PLAY_GetPort(&m_Port);
	Print("m_port:%d",m_Port);
	OpenFile();

	H264_PLAY_Play(m_Port, pVPlayerWnd->GetHWND());
	H264_PLAY_SetFileEndCallBack(m_Port, EOFCallBack, (LONG)this);
	DWORD PlayTime = H264_PLAY_GetFileTime(m_Port);
	CDuiString sTime;
	sTime.Format(_T("%02d:%02d:%02d"), PlayTime / 3600, PlayTime / 60, PlayTime % 60);
	pEndTime->SetText(sTime);
	//pPlay->SetBkImage(sStopNoFocusImg);
	//pPlay->SetFocusedImage(sStopFocusedImg);
	SetTimer(m_hWnd, 1, 1000, NULL);
}

void CPlayerWallWnd::OpenFile()
{
	const char *  ptr;
	CString path;
	path = _T("D:\\NormalRecord\\6\\20161229152102131.h264");
	USES_CONVERSION;
	ptr = T2CA(path);
	H264_PLAY_OpenFile(m_Port, ptr);
}

BOOL CPlayerWallWnd::StopPlay()
{
	return 0;
}

void CPlayerWallWnd::OnBack()
{
	int res;
	int err;
	float pos;
	float space;
	//pos = H264_PLAY_GetPlayPos(m_Port);
	//H264_PLAY_SetPlayPos(m_Port, pos - 0.05);
	
	if (m_nRate < 4) {
		space = 1 / (24*pow(2, m_nRate));
		m_nRate++;
	}
	//KillTimer(m_hWnd,2);
	//Print("space:%d", (int)(space * 1000));
	H264_PLAY_Back(m_Port);
	//SetTimer(m_hWnd,2, 1000,NULL);


	//H264_PLAY_PrevFrame(m_Port);

	//res = H264_PLAY_Back(m_Port);
	err = GetLastError();
	//Print("res:%d,err:%d",res,err);
}

void CPlayerWallWnd::OnFast()
{
	H264_PLAY_Stop(m_Port);
}

void CPlayerWallWnd::OnPlay()
{

}
