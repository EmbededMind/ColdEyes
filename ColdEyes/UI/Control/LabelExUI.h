#pragma once

#include "DuiLib\UIlib.h"
using namespace DuiLib;

class CLabelExUI 
	:public CButtonUI
{
DECLARE_DUICONTROL(CLabelExUI)
public:
	CLabelExUI();
	~CLabelExUI();
	void PaintText(HDC hDC);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetStateEnableText(LPCTSTR pstrText);
	void SetStateDisableText(LPCTSTR pstrText);
	void SetStateTextColor(DWORD Color);
	void SetStateTextFocusColor(DWORD Color);
	void PaintStatusImage(HDC hDC);
	void PaintBkColor(HDC hDC);
	void SetFocusBkColor(DWORD Color);
	void SetSelBkImage(LPCTSTR pstrValue);
	void SetFocusedSelBkImage(LPCTSTR pstrValue);
	void DoEvent(TEventUI &event);
	bool GetValue();
	void SetValue(bool value);
private:
	bool m_Value;
	CDuiString m_stateEnableText;
	CDuiString m_stateDisableText;
	DWORD m_stateTextColor;
	DWORD m_stateTextFocusColor;
	DWORD m_focusBkColor;
	CDuiString m_selbkimage;
	CDuiString m_focusedselbkimage;
};

