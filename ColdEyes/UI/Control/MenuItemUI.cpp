#include "stdafx.h"
#include "MenuItemUI.h"

IMPLEMENT_DUICONTROL(CMenuItemUI)
CMenuItemUI::CMenuItemUI()
	:mFocusedBkColor(0xFFFFFFFF)
{
}

CMenuItemUI::~CMenuItemUI()
{
}

LPCTSTR CMenuItemUI::GetClass() const
{
	return _T("MenuItemUI");
}

void CMenuItemUI::DoEvent(TEventUI & event)
{
	switch (event.Type) {
	case UIEVENT_KEYDOWN:
		{
			CContainerUI* pParentLayout = static_cast<CContainerUI*>(m_pParent);
			int index = pParentLayout->GetItemIndex(this);
			switch (event.wParam) {
				case VK_UP:
					if (index != 0) {
						pParentLayout->GetItemAt(index - 1)->SetFocus();
					}
					break;

				case VK_DOWN:
					if (index < pParentLayout->GetCount() - 1) {
						pParentLayout->GetItemAt(index + 1)->SetFocus();
					}
					break;

				case VK_LEFT:
					break;

				case VK_RIGHT:
					CContainerUI* pLayout = (CContainerUI*)static_cast<CTabLayoutUI*>(m_pManager->FindControl(m_sBindTabLayoutName))->GetItemAt(m_iBindTabIndex);
					CControlUI* pItem;
					pItem = static_cast<CContainerUI*>(pLayout->GetItemAt(0))->GetItemAt(0);
					if (pItem)
						pItem->SetFocus();
					break;
			}
		}
		break;
		
	case UIEVENT_SETFOCUS:
		static_cast<CTabLayoutUI*>(m_pManager->FindControl(m_sBindTabLayoutName))->SelectItem(m_iBindTabIndex);
		break;
	}
	__super::DoEvent(event);
}

void CMenuItemUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	CButtonUI::SetAttribute(pstrName, pstrValue);
	if (_tcscmp(pstrName, _T("focusedbkcolor"))==0) {
		if (*pstrValue == _T('#'))
			pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		mFocusedBkColor = _tcstoul(pstrValue, &pstr, 16);
	}
}

void CMenuItemUI::PaintBkColor(HDC hDC)
{
	if(!m_bFocused){
		CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(m_dwBackColor));
	}
	else {
		CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(mFocusedBkColor));
	}
}
