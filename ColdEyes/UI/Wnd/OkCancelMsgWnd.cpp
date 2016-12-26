#include "stdafx.h"
#include "OkCancelMsgWnd.h"

//DUI_BEGIN_MESSAGE_MAP(CMsgWnd, WindowImplBase)
//DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
//DUI_END_MESSAGE_MAP()

//void CMsgWnd::OnClick(TNotifyUI & msg)
//{
//	CDuiString sName = msg.pSender->GetName();
//	if (_tcscmp(sName, _T("ok_btn")) == 0) {
//		Close(MSGID_OK);
//	}
//	else if (_tcscmp(sName, _T("cancel_btn")) == 0) {
//		Close(MSGID_CANCEL);
//	}
//}


COkCancelMsgWnd::COkCancelMsgWnd()
{
}


COkCancelMsgWnd::~COkCancelMsgWnd()
{
}


void COkCancelMsgWnd::OnFinalMessage(HWND)
{
}

CDuiString COkCancelMsgWnd::GetSkinFile()
{
	return m_sSkinType;
}

LPCTSTR COkCancelMsgWnd::GetWindowClassName(void) const
{
	return _T("MsgWnd");
}

void COkCancelMsgWnd::Notify(TNotifyUI & msg)
{
	return WindowImplBase::Notify(msg);
}

void COkCancelMsgWnd::InitWindow()
{
	pButton_ok = (CButtonUI*)m_pm.FindControl(_T("ok_btn"));
	if (pButton_ok)
		pButton_ok->OnEvent += MakeDelegate(this, &COkCancelMsgWnd::OnButtonOk);
	pButton_cancel = (CButtonUI*)m_pm.FindControl(_T("cancel_btn"));
	if (pButton_cancel)
		pButton_cancel->OnEvent += MakeDelegate(this, &COkCancelMsgWnd::OnButtonCancel);
}

void COkCancelMsgWnd::OnTimer(UINT, WPARAM, LPARAM, BOOL & bHandled)
{
}

LRESULT COkCancelMsgWnd::OnSysCommand(UINT, WPARAM, LPARAM, BOOL & bHandled)
{
	return LRESULT();
}

LRESULT COkCancelMsgWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	return LRESULT();
}

void COkCancelMsgWnd::SetMsg(LPCTSTR text1, LPCTSTR text2)
{
	if (_tcscmp(m_sSkinType, _T("mb_ok.xml")) == 0 || _tcscmp(m_sSkinType,_T("mb_okcancel.xml"))==0) {
		CControlUI* pText1 = (CControlUI*)m_pm.FindControl(_T("Text1"));
		CControlUI* pText2 = (CControlUI*)m_pm.FindControl(_T("Text2"));
		if (text1) {
			pText1->SetText(text1);
			pText2->SetText(text2);
		}
		else {
			pText2->SetAttribute(_T("align"), _T("center"));
			pText2->SetText(text2);
		}
	}
	else if (_tcscmp(m_sSkinType, _T("mb_copyvideo_request.xml")) == 0) {
		CControlUI* pText = (CControlUI*)m_pm.FindControl(_T("Time"));
		pText->SetText(text1);
	}
	else if (_tcscmp(m_sSkinType, _T("mb_update_request.xml")) == 0) {
		CControlUI* pOldVersion = (CControlUI*)m_pm.FindControl(_T("old_version"));
		CControlUI* pNewVersion = (CControlUI*)m_pm.FindControl(_T("new_version"));

		pOldVersion->SetText(text1);
		pNewVersion->SetText(text2);
	}
}

bool COkCancelMsgWnd::OnButtonOk(void * param)
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

bool COkCancelMsgWnd::OnButtonCancel(void * param)
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

		case VK_RETURN:
			Close(MSGID_CANCEL);
			return false;
			break;
		}
		break;
	}
	return true;
}
