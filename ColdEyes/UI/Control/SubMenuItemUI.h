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
	~CSubMenuItemUI();

	virtual LPCTSTR GetClass() const;
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetParentMenuItem(LPCTSTR pstrValue);
	CMenuItemUI* GetParentItem();

private:
	LPCTSTR	m_sParentMenuName;
	CMenuItemUI* m_pParentMenu;
};

