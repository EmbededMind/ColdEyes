#include "stdafx.h"
#include "SwitchExUI.h"

IMPLEMENT_DUICONTROL(CSwitchExUI)
CSwitchExUI::CSwitchExUI()
	:mValue(false)
{
}


CSwitchExUI::~CSwitchExUI()
{
}

void CSwitchExUI::DoEvent(TEventUI & event)
{
	switch (event.Type)
	{
	case UIEVENT_KEYDOWN:
		//m_pManager->SendNotify(this,DUI_MSGTYPE_SWITCH,event.wParam,event.lParam);
		break;

	case UIEVENT_SETFOCUS:
		SetBkColor(0xFF4198FE);
		break;

	case UIEVENT_KILLFOCUS:
		SetBkColor(0xFFF3F3F3);
		break;
	}
	CButtonUI::DoEvent(event);
}

void CSwitchExUI::PaintStatusImage(HDC hDC)
{
	CButtonUI::PaintStatusImage(hDC);
	if (mValue == true) {
		DrawImage(hDC, sOnImage);
	}
	else {
		DrawImage(hDC, sOffImage);
	}
}

void CSwitchExUI::SetValue(bool value)
{
	mValue = value;
}

bool CSwitchExUI::GetValue()
{
	return mValue;
}

void CSwitchExUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcsicmp(pstrName, _T("onimage")) == 0)
		SetOnImage(pstrValue);
	else if (_tcsicmp(pstrName, _T("offimage")) == 0)
		SetOffImage(pstrValue);
	CButtonUI::SetAttribute(pstrName, pstrValue);
}

void CSwitchExUI::SetOnImage(CDuiString pstrValue)
{
	sOnImage = pstrValue;
}

void CSwitchExUI::SetOffImage(CDuiString pstrValue)
{
	sOffImage = pstrValue;
}

