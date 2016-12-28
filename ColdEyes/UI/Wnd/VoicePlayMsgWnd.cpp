#include "stdafx.h"
#include "VoicePlayMsgWnd.h"


CVoicePlayMsgWnd::CVoicePlayMsgWnd()
{
}


CVoicePlayMsgWnd::~CVoicePlayMsgWnd()
{
}


CDuiString CVoicePlayMsgWnd::GetSkinFile()
{
	return m_sSkinType;
}

LPCTSTR CVoicePlayMsgWnd::GetWindowClassName(void) const
{
	return _T("MsgWnd");
}

void CVoicePlayMsgWnd::Notify(TNotifyUI & msg)
{
	return WindowImplBase::Notify(msg);
}

void CVoicePlayMsgWnd::InitWindow()
{
	m_pm.SetDPI( ((CColdEyesDlg*)AfxGetMainWnd())->mMenu->GetDpi());
	pButton_ok = (CButtonUI*)m_pm.FindControl(_T("ok_btn"));
	if (pButton_ok)
		pButton_ok->OnEvent += MakeDelegate(this, &CVoicePlayMsgWnd::OnButtonOk);
	pButton_cancel = (CButtonUI*)m_pm.FindControl(_T("cancel_btn"));
	if (pButton_cancel)
		pButton_cancel->OnEvent += MakeDelegate(this, &CVoicePlayMsgWnd::OnButtonCancel);
	pButton_reRecord = (CButtonUI*)m_pm.FindControl(_T("rerecord_btn"));
	if (pButton_reRecord)
		pButton_reRecord->OnEvent += MakeDelegate(this, &CVoicePlayMsgWnd::OnButtonReRecord);
	pSlider_progress = (CSliderUI*)m_pm.FindControl(_T("progress_slider"));
}


LRESULT CVoicePlayMsgWnd::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = TRUE;
	return 0;
}

LRESULT CVoicePlayMsgWnd::OnSysCommand(UINT, WPARAM, LPARAM, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0L;
}

LRESULT CVoicePlayMsgWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	switch (uMsg) {	

	case WM_TIMER:	
		OnTimer(uMsg, wParam, lParam, bHandled);
		break;
	//-----------------------------------------------

	}

	bHandled = FALSE;
	return 0;
}

bool CVoicePlayMsgWnd::OnButtonOk(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_RIGHT:
			if (pButton_cancel) {
				pButton_cancel->SetFocus();
			}
			return false;
			break;

		case VK_RETURN:
			Close(MSGID_OK);
			break;
		}
		break;
	}
	return true;
}

bool CVoicePlayMsgWnd::OnButtonCancel(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_LEFT:
			if (pButton_ok) {
				pButton_ok->SetFocus();
			}
			return false;
			break;

		case VK_RIGHT:
			if (pButton_reRecord) {
				pButton_reRecord->SetFocus();
			}
			return false;
			break;

		case VK_RETURN:
			Close(MSGID_OK);
			break;
		}
		break;
	}
	return true;
}

bool CVoicePlayMsgWnd::OnButtonReRecord(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_LEFT:
			if (pButton_cancel) {
				pButton_cancel->SetFocus();
			}
			return false;
			break;

		case VK_RETURN:
			Close(MSGID_OK);
			break;
		}
		break;
	}
	return true;
}
