#pragma once

#include "DuiLib\UIlib.h"
using namespace DuiLib;

class CCameraNameElementUI
	: public CButtonUI
{
DECLARE_DUICONTROL(CCameraNameElementUI)

	CCameraNameElementUI();
	~CCameraNameElementUI();

	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	virtual void DoEvent(TEventUI& event);

private:
	CDuiString m_sBindShowControlName;
	DWORD m_focusedBkColor;
	DWORD m_bkColor;
};