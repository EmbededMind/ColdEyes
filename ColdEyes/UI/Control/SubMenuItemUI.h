#pragma once

#include "DuiLib\UIlib.h"
#include "MenuItemUI.h"

using namespace DuiLib;

class CSubMenuItemUI
	:public CMenuItemUI 
{
DECLARE_DUICONTROL(CSubMenuItemUI)
public:
	CSubMenuItemUI();
	CSubMenuItemUI(CContainerUI* pParent,const CString& text, int iInx);
	~CSubMenuItemUI();

	virtual LPCTSTR GetClass() const;
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetOnwerMenuItemName(LPCTSTR pstrValue);
	LPCTSTR GetOnwerMenuItemName();

private:
	CDuiString	m_sOnwerMenuName;
	//CMenuItemUI* m_pOnwerMenu;
};

