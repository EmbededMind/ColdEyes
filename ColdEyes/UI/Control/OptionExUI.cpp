#include "stdafx.h"
#include "OptionExUI.h"


IMPLEMENT_DUICONTROL(COptionExUI)

COptionExUI::COptionExUI() 
{

}

COptionExUI::~COptionExUI()
{
}

void COptionExUI::PaintBkImage(HDC hDC)
{
	if (m_bFocused) {
		if (IsSelected()) {
			DrawImage(hDC, (LPCTSTR)m_sFocusedSelImage);
		}
		else {
			DrawImage(hDC, (LPCTSTR)m_sFocusedUnSelImage);
		}
	}
	else {
		if (IsSelected()) {
			DrawImage(hDC, (LPCTSTR)m_sNoFocusedSelImage);
		}
		else {
			DrawImage(hDC, (LPCTSTR)m_sNoFocusedUnSelImage);
		}
	}
	//Invalidate();
	//__super::PaintBkImage(hDC);
}

void COptionExUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcsicmp(pstrName, _T("foucsedselimage")) == 0)
		m_sFocusedSelImage = pstrValue;
	else if (_tcsicmp(pstrName, _T("focusedunselimage")) == 0)
		m_sFocusedUnSelImage = pstrValue;
	else if (_tcsicmp(pstrName, _T("nofocusedselimage")) == 0)
		m_sNoFocusedSelImage = pstrValue;
	else if (_tcsicmp(pstrName, _T("nofocusedunselimage")) == 0)
		m_sNoFocusedUnSelImage = pstrValue;

	__super::SetAttribute(pstrName, pstrValue);
}
