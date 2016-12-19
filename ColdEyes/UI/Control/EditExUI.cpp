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
