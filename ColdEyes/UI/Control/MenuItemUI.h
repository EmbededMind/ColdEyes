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
	virtual void PaintBkColor(HDC hDC);
	virtual void PaintText(HDC hDC);
	void SetStatus(int status);
	void PaintStatusImage(HDC hDC);

protected:
	DWORD mFocusedBkColor;
	DWORD mNoFocusedSelBkColor;

	UINT  mState;

};
