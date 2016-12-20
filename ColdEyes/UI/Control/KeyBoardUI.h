#pragma once

#include "DuiLib\UIlib.h"

#include <vector>

using namespace DuiLib;

class CKeyBoardUI
	:public CVerticalLayoutUI
{
DECLARE_DUICONTROL(CKeyBoardUI)

	CKeyBoardUI();
	CKeyBoardUI(UINT8 line, UINT8 row, CDuiString* pKeyText);
	~CKeyBoardUI();

	void SetAttribute(LPCTSTR pstrName, LPCTSTR);
	virtual void DoEvent(TEventUI& event);

	void Layout();

	void AddKeyElement();
	void SetKeyElementText();
	void SetKeyElementText(UINT line,UINT row, CDuiString text);

	void SetKeyElementBkColor(DWORD Color);
	void SetKeyElementBkColor(UINT line, UINT row, DWORD Color);

	void SetKeyElementTextColor(DWORD Color);
	void SetKeyElementTextColor(UINT line, DWORD Color);
	void SetKeyElementTextColor(UINT line, UINT row ,DWORD Color);

	void SetKeyElementFocusedBkColor(DWORD Color);
	void SetKeyElementFocusedBkColor(UINT line, UINT row, DWORD Color);

	void SetKeyElementFocusedTextColor(DWORD Color);
	void SetKeyElementFocusedTextColor(UINT line, UINT row ,DWORD Color);

	void SetKeyElementBkImage(LPCTSTR image);
	void SetKeyElementBkImage(UINT line, UINT row, LPCTSTR image);

	void SetKeyElementFocusedImage(LPCTSTR image);
	void SetKeyElementFocusedImage(UINT line, UINT row, LPCTSTR image);

	void SetKeyElementFont(int font);

	void SetShowStringControl(CControlUI* pControl);
	void SetShowStringControlText(CDuiString text);

	bool OnKeyClickedListener(void* param);

private:
	SIZE m_Size;
	UINT8 m_line;
	UINT8 m_row;
	CDuiString* m_pKeyText;
	vector<CButtonUI*> m_pKeyElement;
	vector<CHorizontalLayoutUI*> m_pLineLayout;
	UINT8 m_focusInx;
	CControlUI* m_pShowControl;
};