#include "stdafx.h"
#include "SubMenuItemUI.h"

IMPLEMENT_DUICONTROL(CSubMenuItemUI)
CSubMenuItemUI::CSubMenuItemUI()
{
}

CSubMenuItemUI::~CSubMenuItemUI()
{
}

LPCTSTR CSubMenuItemUI::GetClass() const
{
	return _T("SubMenuItemUI");
}

void CSubMenuItemUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	CMenuItemUI::SetAttribute(pstrName, pstrValue);
	//if (_tcscmp(pstrName, _T("parentmenuitem")) == 0) {
	//	SetParentMenuItem(pstrName);
	//}
}


void CSubMenuItemUI::SetParentMenuItem(LPCTSTR pstrValue)
{
	m_pParentMenu = static_cast<CMenuItemUI*>(m_pManager->FindControl(pstrValue));
}

CMenuItemUI * CSubMenuItemUI::GetParentItem()
{
	return m_pParentMenu;
}
