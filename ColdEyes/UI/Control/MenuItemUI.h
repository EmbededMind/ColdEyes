#pragma once


#include "DuiLib\UIlib.h"

using namespace DuiLib;

class CMenuItemUI
	:public CButtonUI
{
DECLARE_DUICONTROL(CMenuItemUI)
public:
	CMenuItemUI();
	~CMenuItemUI(); 
	virtual LPCTSTR GetClass() const;
	virtual void DoEvent(TEventUI& event);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void PaintBkColor(HDC hDC);

protected:
	DWORD mFocusedBkColor;
};
