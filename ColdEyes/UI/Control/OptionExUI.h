#pragma once

#include "DuiLib\UIlib.h"

using namespace DuiLib;

class COptionExUI 
	:public COptionUI
{
	DECLARE_DUICONTROL(COptionExUI)

	public:
		COptionExUI();
		~COptionExUI();

		void PaintBkImage(HDC hDC);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

private:
	CDuiString		m_sFocusedSelImage;
	CDuiString		m_sFocusedUnSelImage;
	CDuiString		m_sNoFocusedSelImage;
	CDuiString		m_sNoFocusedUnSelImage;

};

