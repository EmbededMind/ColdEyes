#include "stdafx.h"
#include "CameraNameElementUI.h"

IMPLEMENT_DUICONTROL(CCameraNameElementUI)

CCameraNameElementUI::CCameraNameElementUI()
{

}

CCameraNameElementUI::~CCameraNameElementUI()
{

}

void CCameraNameElementUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcscmp(pstrName, _T("focusedbkcolor")) == 0) {
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		m_focusedBkColor = _tcstoul(pstrValue, &pstr, 16);
	}
	else if(_tcsicmp(pstrName, _T("nofocusedbkcolor")) == 0){
		if (*pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		m_bkColor = _tcstoul(pstrValue, &pstr, 16);
	}
	else if (_tcsicmp(pstrName, _T("bindshow")) == 0) {
		m_sBindShowControlName = pstrValue;
	}
	__super::SetAttribute(pstrName, pstrValue);
}

void CCameraNameElementUI::DoEvent(TEventUI & event)
{
	CVerticalLayoutUI* pParentLayout;
	CVerticalLayoutUI* pLayout;

	CContainerUI* pNextLayout;
	CContainerUI* pLastLayout;
	CButtonUI* pBindShowControl;
	switch (event.Type) {
	case UIEVENT_KEYDOWN:
		pParentLayout = (CVerticalLayoutUI*)(GetParent()->GetParent());
		pLayout = (CVerticalLayoutUI*)GetParent();
		switch (event.wParam) {
		case VK_UP:
			if (pParentLayout->GetItemIndex(pLayout)) {
				pLastLayout = (CContainerUI*)pParentLayout->GetItemAt(pParentLayout->GetItemIndex(pLayout) - 1);
				if(pLastLayout)
					pLastLayout->GetItemAt(pLayout->GetItemIndex(this))->SetFocus();
			}
			break;

		case VK_DOWN:
			if (pParentLayout->GetItemIndex(pLayout) < pParentLayout->GetCount() - 1) {
				pNextLayout = (CContainerUI*)pParentLayout->GetItemAt(pParentLayout->GetItemIndex(pLayout) + 1);
				if(pNextLayout)
					if (pNextLayout->GetItemAt(pLayout->GetItemIndex(this))) {
						pNextLayout->GetItemAt(pLayout->GetItemIndex(this))->SetFocus();
					}
			}
			break;

		case VK_LEFT:
			if (pLayout->GetItemIndex(this)) {

				pLayout->GetItemAt(pLayout->GetItemIndex(this)-1)->SetFocus();
			}
			else {
				pLastLayout = (CContainerUI*)pParentLayout->GetItemAt(pParentLayout->GetItemIndex(pLayout) - 1);
				if (pLastLayout)
					pLastLayout->GetItemAt(pLastLayout->GetCount()-1)->SetFocus();
			}
			break;

		case VK_RIGHT:
			if (pLayout->GetItemIndex(this) < pLayout->GetCount() - 1) {
				pLayout->GetItemAt(pLayout->GetItemIndex(this)+1)->SetFocus();
			}
			else {
				pNextLayout = (CContainerUI*)pParentLayout->GetItemAt(pParentLayout->GetItemIndex(pLayout) + 1);
				if (pNextLayout)
						pNextLayout->GetItemAt(0)->SetFocus();
			}
			break;

		case VK_RETURN:
			if (m_sBindShowControlName) {
				m_pManager->FindControl(m_sBindShowControlName)->SetText(GetText());
			}
			break;

		case VK_BACK:
			if (m_sBindShowControlName) {
				m_pManager->FindControl(m_sBindShowControlName)->SetFocus();
				//pParentLayout->SetVisible(false);
			}
			break;
		}
		break;
		
	case UIEVENT_SETFOCUS:
		SetBkColor(m_focusedBkColor);
		break;

	case UIEVENT_KILLFOCUS:
		SetBkColor(m_bkColor);
		break;
	}
	__super::DoEvent(event);
}
