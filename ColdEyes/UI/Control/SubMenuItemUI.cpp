#include "stdafx.h"
#include "SubMenuItemUI.h"

IMPLEMENT_DUICONTROL(CSubMenuItemUI)
CSubMenuItemUI::CSubMenuItemUI()
{
}

CSubMenuItemUI::CSubMenuItemUI(CContainerUI * pParent,const CString & text, int iInx)
{
	SetText(text);
	pParent->AddAt(this, iInx);
	SetAttribute(_T("style"), _T("sytle_submenu"));

	CControlUI* p = new CControlUI;
	pParent->AddAt(p, iInx + 1);
	p->SetAttribute(_T("style"), _T("control"));
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
	if (_tcsicmp(pstrName, _T("onwer")) == 0){
		SetOnwerMenuItemName(pstrValue);
	}
	CMenuItemUI::SetAttribute(pstrName, pstrValue);
}


void CSubMenuItemUI::SetOnwerMenuItemName(LPCTSTR pstrValue)
{
	if (pstrValue) {
		m_sOnwerMenuName = pstrValue;
	}
}

LPCTSTR CSubMenuItemUI::GetOnwerMenuItemName()
{
	return m_sOnwerMenuName;
}
