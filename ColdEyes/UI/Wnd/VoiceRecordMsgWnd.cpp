#include "stdafx.h"
#include "VoiceRecordMsgWnd.h"


CVoiceRecordMsgWnd::CVoiceRecordMsgWnd()
{
}


CVoiceRecordMsgWnd::~CVoiceRecordMsgWnd()
{
}


CDuiString CVoiceRecordMsgWnd::GetSkinFile()
{
	return m_sSkinType;
}

LPCTSTR CVoiceRecordMsgWnd::GetWindowClassName(void) const
{
	return _T("MsgWnd");
}

void CVoiceRecordMsgWnd::Notify(TNotifyUI & msg)
{
	return WindowImplBase::Notify(msg);
}

void CVoiceRecordMsgWnd::InitWindow()
{
	m_pm.SetDPI( ((CColdEyesDlg*)AfxGetMainWnd())->mMenu->GetDpi());
	m_pRecordingImage = (CLabelUI*)(m_pm.FindControl(_T("redpoint")));
	m_pShowRecordTime = (CLabelUI*)(m_pm.FindControl(_T("recordtime")));
	m_pShowRecordTime->SetText(_T("60\""));
	m_timeCnt = 0;
}


LRESULT CVoiceRecordMsgWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	switch (wParam) {
	case 1:
		m_timeCnt++;
		if (m_pRecordingImage->IsVisible()) {
			m_pRecordingImage->SetVisible(false);
		}
		else {
			m_pRecordingImage->SetVisible(true);
		}

		if (m_timeCnt == 2) {
			int iTime;
			CDuiString sTime;
			m_timeCnt = 0;
			iTime = StrToInt(m_pShowRecordTime->GetText());
			if (iTime > 0) {
				iTime -= 1;
				sTime.Format(_T("%d\""),iTime);
				m_pShowRecordTime->SetText(sTime);
			}
			else {
				KillTimer(m_hWnd,1);
				Close(1);
			}
		}
		break;
	}

	bHandled = TRUE;
	return 0;
}

LRESULT CVoiceRecordMsgWnd::OnSysCommand(UINT, WPARAM, LPARAM, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0L;
}

LRESULT CVoiceRecordMsgWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	switch (uMsg) {	

	case WM_TIMER:	
		OnTimer(uMsg, wParam, lParam, bHandled);
		break;
	//-----------------------------------------------
	case WM_KEYDOWN:
		if (GetKeyState(VK_CONTROL) && !(lParam & 0x20000000)) {
			//开始录制
			if (wParam == 'T') { 
				CTextUI *pItem = static_cast<CTextUI*>(m_pm.FindControl(_T("Text2")));
				int id = SetTimer(m_hWnd, 1, 500, NULL);
				Print("time id :%d",id);
				pItem->SetText(_T("松开          按键，结束录制。"));
			}
			//停止录制
			else if (wParam == 'O') {
				KillTimer(m_hWnd, 1);
				Close(1);
			}
		}
		break;


	}

	bHandled = FALSE;
	return 0;
}
