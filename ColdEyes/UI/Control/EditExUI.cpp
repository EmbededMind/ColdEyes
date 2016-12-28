#include "stdafx.h"
#include "EditExUI.h"

IMPLEMENT_DUICONTROL(CEditExUI)
CEditExUI::CEditExUI()
	:isEditing(false)
{
}


CEditExUI::~CEditExUI()
{
}


void CEditExUI::DoEvent(TEventUI &event)
{
	if (event.Type == UIEVENT_KEYDOWN){
		//m_pManager->SendNotify(this, DUI_MSGTYPE_EDIT,event.wParam,event.lParam);
	}


	if (event.Type == UIEVENT_SETFOCUS){
		SetBkColor(0xFFD7E9FF);
	}
	else if (event.Type == UIEVENT_KILLFOCUS) {
		if(isEditing==false)
			SetBkColor(0xFFEBEBEB);
	}

	CButtonUI::DoEvent(event);
}

void CEditExUI::PaintBorder(HDC hDC)
{
	int nBorderSize;
	SIZE cxyBorderRound;
	RECT rcBorderSize;
	if (m_pManager) {
		nBorderSize = GetManager()->GetDPIObj()->Scale(m_nBorderSize);
		cxyBorderRound = GetManager()->GetDPIObj()->Scale(m_cxyBorderRound);
		rcBorderSize = GetManager()->GetDPIObj()->Scale(m_rcBorderSize);
	}
	else {
		nBorderSize = m_nBorderSize;
		cxyBorderRound = m_cxyBorderRound;
		rcBorderSize = m_rcBorderSize;

	}

	if (m_dwBorderColor != 0 || m_dwFocusBorderColor != 0) {
		//»­Ô²½Ç±ß¿ò
		if (nBorderSize > 0 && (cxyBorderRound.cx > 0 || cxyBorderRound.cy > 0)) {
			if (GetStatus()) {
				CRenderEngine::DrawRoundRect(hDC, m_rcItem, nBorderSize, cxyBorderRound.cx, cxyBorderRound.cy, GetAdjustColor(m_dwFocusBorderColor), m_nBorderStyle);
			}
			else if (IsFocused() && m_dwFocusBorderColor != 0)
				CRenderEngine::DrawRoundRect(hDC, m_rcItem, nBorderSize, cxyBorderRound.cx, cxyBorderRound.cy, GetAdjustColor(m_dwFocusBorderColor), m_nBorderStyle);
			else
				CRenderEngine::DrawRoundRect(hDC, m_rcItem, nBorderSize, cxyBorderRound.cx, cxyBorderRound.cy, GetAdjustColor(m_dwBorderColor), m_nBorderStyle);
		}
	}
	//__super::PaintBorder(hDC);
}

void CEditExUI::SetName(CString name)
{
	SetUserData(name);
	SetText(name);
}

void CEditExUI::SetStatus(bool newStatus)
{
	isEditing = newStatus;
}

bool CEditExUI::GetStatus()
{
	return isEditing;
}
