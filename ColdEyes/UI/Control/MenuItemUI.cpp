#include "stdafx.h"
#include "MenuItemUI.h"

IMPLEMENT_DUICONTROL(CMenuItemUI)
CMenuItemUI::CMenuItemUI()
	:mFocusedBkColor(0xFFFFFFFF),
	mState(0),
	IsMark(0)
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
						pParentLayout->GetItemAt(index - 2)->SetFocus();
					}
					break;

				case VK_DOWN:
					if (index < pParentLayout->GetCount() - 2) {
						pParentLayout->GetItemAt(index + 2)->SetFocus();
					}
					break;

				case VK_LEFT:
					break;

				case VK_RIGHT:
					CContainerUI* pLayout = (CContainerUI*)static_cast<CTabLayoutUI*>(m_pManager->FindControl(m_sBindTabLayoutName))->GetItemAt(m_iBindTabIndex);
					CControlUI* pItem;
					pItem = static_cast<CContainerUI*>(pLayout->GetItemAt(0))->GetItemAt(0);
					if (pItem) {
						pItem->SetFocus();
					}
					break;
			}
		}
		break;
		
	case UIEVENT_SETFOCUS:
		if (m_pManager->FindControl(m_sBindTabLayoutName)) {
			static_cast<CTabLayoutUI*>(m_pManager->FindControl(m_sBindTabLayoutName))->SelectItem(m_iBindTabIndex);
		}
		break;
	}
	__super::DoEvent(event);
}

void CMenuItemUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcsicmp(pstrName, _T("focusedbkcolor"))==0) {
		if (*pstrValue == _T('#'))
			pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		mFocusedBkColor = _tcstoul(pstrValue, &pstr, 16);
	}
	else if (_tcsicmp(pstrName, _T("nofocusedselbkcolor")) == 0) {
		if (*pstrValue == _T('#'))
			pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		mNoFocusedSelBkColor = _tcstoul(pstrValue, &pstr, 16);
	}
	else if (_tcsicmp(pstrName, _T("mark")) == 0) {
		if (_tcsicmp(pstrValue, _T("true")) == 0) {
			IsMark = true;
		}
	}

	__super::SetAttribute(pstrName, pstrValue);
}

void CMenuItemUI::PaintBkColor(HDC hDC)
{
	if(m_bFocused){
			CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(mFocusedBkColor));
	}
	else {
		if (mState) {
			CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(mNoFocusedSelBkColor));
		}
		else {
			CRenderEngine::DrawColor(hDC, m_rcItem, GetAdjustColor(m_dwBackColor));
		}

	}
}

void CMenuItemUI::PaintText(HDC hDC)
{
	if (mState) {
		
		RECT m_rcTextPadding = CButtonUI::m_rcTextPadding;
		GetManager()->GetDPIObj()->Scale(&m_rcTextPadding);
		RECT rc = m_rcItem;
		rc.left += m_rcTextPadding.left;
		rc.right -= m_rcTextPadding.right;
		rc.top += m_rcTextPadding.top;
		rc.bottom -= m_rcTextPadding.bottom;
		CRenderEngine::DrawText(hDC, m_pManager, rc, GetText(), GetFocusedTextColor(), \
			m_iFont, GetTextStyle());
		return;
	}
	__super::PaintText(hDC);
}

void CMenuItemUI::SetStatus(int status)
{
	mState = status;
}

void CMenuItemUI::PaintStatusImage(HDC hDC)
{
	__super::PaintStatusImage(hDC);

	if (mState) {
		DrawImage(hDC, (LPCTSTR)m_sFocusedImage);
	}
	if (IsMark) {
		PaintSuperScript(hDC);
	}
}

void CMenuItemUI::PaintSuperScript(HDC hDC)
{
	RECT textPos = GetPos();
	RECT rcPos = { 259, 10, 294, 45 };
	CDuiString dest;
	CDuiString text = _T("99");
	dest.Format(_T("file='image\\ÍÖÔ²ÐÎ.png' dest='%d,%d,%d,%d'"), rcPos.left, rcPos.top, rcPos.right, rcPos.bottom);
	DrawImage(hDC, dest);
	
	textPos.left += m_pManager->GetDPIObj()->Scale(rcPos.left);
	textPos.top += m_pManager->GetDPIObj()->Scale(rcPos.top);
	textPos.right = textPos.left + m_pManager->GetDPIObj()->Scale(35);
	textPos.bottom = textPos.top + m_pManager->GetDPIObj()->Scale(38);

	m_uTextStyle &= ~(DT_LEFT | DT_RIGHT);
	m_uTextStyle |= DT_CENTER;
	m_uTextStyle &= ~(DT_TOP | DT_BOTTOM | DT_WORDBREAK);
	m_uTextStyle |= (DT_VCENTER | DT_SINGLELINE);
	CRenderEngine::DrawText(hDC, m_pManager, textPos, text, 0xFFFFFFFF, 1, m_uTextStyle);
}

void CMenuItemUI::SetMark(bool isMark)
{
	IsMark = isMark;
}
