#pragma once
#include "DuiLib\UIlib.h"

using namespace DuiLib;

class CSliderExUI
	:public CSliderUI 
{
DECLARE_DUICONTROL(CSliderExUI)

public:
	CSliderExUI();
	~CSliderExUI();

	  virtual void DoEvent(TEventUI& event);
	  //virtual void PaintBkColor(HDC hDC);
	 // virtual void PaintBkImage(HDC hDC);
	  virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

private:
	CSize m_BkImageSize;
	CSize m_InvalidSize;
	DWORD m_FocusedBkColor;
	CDuiString m_bindBk;
	CDuiString m_focusedbkimage;
	CDuiString m_bkimage;
};