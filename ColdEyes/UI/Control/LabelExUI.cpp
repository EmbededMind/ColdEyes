#include "stdafx.h"
#include "LabelExUI.h"

IMPLEMENT_DUICONTROL(CLabelExUI)
CLabelExUI::CLabelExUI()
	:m_stateEnableText(_T("")),
	m_stateDisableText(_T("")),
	m_Value(false)
{
}


CLabelExUI::~CLabelExUI()
{
}


void CLabelExUI::PaintText(HDC hDC)
{
	CButtonUI::PaintText(hDC);
	RECT rc = m_rcItem;
	RECT m_rcTextPadding = CLabelUI::m_rcTextPadding;
	UINT TextStyle;
	if (m_Value)
	{
		if (m_stateEnableText.IsEmpty())return;

		rc.right -= 45;
		TextStyle = m_uTextStyle;
		TextStyle &= ~(DT_LEFT | DT_CENTER);
		TextStyle |= DT_RIGHT;
		if (m_bFocused)
		{
			CRenderEngine::DrawText(hDC, m_pManager, rc, m_stateEnableText, m_stateTextFocusColor, \
				m_iFont, TextStyle);
		}
		else
		{
			CRenderEngine::DrawText(hDC, m_pManager, rc, m_stateEnableText, m_stateTextColor, \
				m_iFont, TextStyle);
		}
	}
	else
	{
		if (m_stateDisableText.IsEmpty())return;

		rc.right -= 45;
		TextStyle = m_uTextStyle;
		TextStyle &= ~(DT_LEFT | DT_CENTER);
		TextStyle |= DT_RIGHT;
		if (m_bFocused)
		{
			CRenderEngine::DrawText(hDC, m_pManager, rc, m_stateDisableText, m_stateTextFocusColor, \
				m_iFont, TextStyle);
		}
		else
		{
			CRenderEngine::DrawText(hDC, m_pManager, rc, m_stateDisableText, m_stateTextColor, \
				m_iFont, TextStyle);
		}
	}
}

void CLabelExUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcsicmp(pstrName, _T("stateenabletext")) == 0)
		SetStateEnableText(pstrValue);
	else if (_tcsicmp(pstrName, _T("statedisabletext")) == 0)
		SetStateDisableText(pstrValue);
	else if (_tcsicmp(pstrName, _T("statetextcolor")) == 0)
	{
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetStateTextColor(clrColor);
	}
	else if (_tcsicmp(pstrName, _T("statetextfocuscolor")) == 0)
	{
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetStateTextFocusColor(clrColor);
	}
	else if (_tcsicmp(pstrName, _T("focusbkcolor")) == 0)
	{
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		SetFocusBkColor(clrColor);
	}
	else if (_tcsicmp(pstrName, _T("selbkimage")) == 0)
	{
		SetSelBkImage(pstrValue);
	}
	else if (_tcsicmp(pstrName, _T("focusedselbkimage")) == 0)
	{
		SetFocusedSelBkImage(pstrValue);
	}
	CButtonUI::SetAttribute(pstrName, pstrValue);
}

void CLabelExUI::SetStateEnableText(LPCTSTR pstrText)
{
	m_stateEnableText = pstrText;
}

void CLabelExUI::SetStateDisableText(LPCTSTR pstrText)
{
	m_stateDisableText = pstrText;
}

void CLabelExUI::SetStateTextColor(DWORD Color)
{
	m_stateTextColor = Color;
}

void CLabelExUI::SetStateTextFocusColor(DWORD Color)
{
	m_stateTextFocusColor = Color;
}

void CLabelExUI::PaintStatusImage(HDC hDC)
{
	CButtonUI::PaintStatusImage(hDC);
	if (m_Value)
	{
		if (m_bFocused)
		{
			if (!m_focusedselbkimage.IsEmpty())
				DrawImage(hDC, (LPCTSTR)m_focusedselbkimage);
		}
		else
		{
			if(!m_selbkimage.IsEmpty())
				DrawImage(hDC, (LPCTSTR)m_selbkimage);
		}
	}
}

void CLabelExUI::PaintBkColor(HDC hDC)
{
	if (!m_bFocused)
	{
		CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(m_dwBackColor));
	}
	else
	{
		CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(m_focusBkColor));
	}
}

void CLabelExUI::SetFocusBkColor(DWORD Color)
{
	m_focusBkColor = Color;
}

void CLabelExUI::SetFocusedSelBkImage(LPCTSTR pstrValue)
{
	m_focusedselbkimage = pstrValue;
}

void CLabelExUI::SetSelBkImage(LPCTSTR pstrValue)
{
	m_selbkimage = pstrValue;
}

void CLabelExUI::DoEvent(TEventUI & event)
{
	__super::DoEvent(event);
}


bool CLabelExUI::GetValue()
{
	return m_Value;
}

void CLabelExUI::SetValue(bool value)
{
	m_Value = value;
}

