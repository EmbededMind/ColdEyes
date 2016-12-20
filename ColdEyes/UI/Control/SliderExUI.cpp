#include "stdafx.h"
#include "SliderExUI.h"

IMPLEMENT_DUICONTROL(CSliderExUI)

CSliderExUI::CSliderExUI()
{
}

CSliderExUI::~CSliderExUI()
{
}

void CSliderExUI::DoEvent(TEventUI & event)
{

	__super::DoEvent(event);
}

void CSliderExUI::PaintBkColor(HDC hDC)
{
	CRect m_rc;
	if (m_bFocused)
	{
		m_rc = m_rcPaint;
		RECT thumbsize = GetThumbRect();
		int thumbHeight = thumbsize.bottom - thumbsize.top;
		m_rc = m_rcPaint;

		m_rc.left -= 176;
		m_rc.top -= (m_InvalidSize.cy / 2 - thumbHeight / 2);
		m_rc.bottom = m_rc.top + m_InvalidSize.cy;
		m_rc.right += 184;
		CRenderEngine::DrawColor(hDC, m_rc, GetAdjustColor(m_FocusedBkColor));
	}
	InvalidateRect(m_pManager->GetPaintWindow(), m_rc, true);
}

void CSliderExUI::PaintBkImage(HDC hDC)
{
	CRect m_rc;
	RECT thumbsize = GetThumbRect();

	int thumbHeight = thumbsize.bottom - thumbsize.top;
	m_rc = m_rcPaint;
	m_rc.left -= 176;
	m_rc.top -= 28;
	m_rc.bottom += 28;
	m_rc.right += 184;
	//m_rc.left -= (m_BkImageSize.cx / 2 - GetWidth());
	//m_rc.right = m_rc.right + GetWidth();
	//m_rc.left -= 176;
	//m_rc.top  -= (m_BkImageSize.cy/2 - thumbHeight/2)+4;
	//m_rc.bottom = m_rc.top + m_BkImageSize.cy;
	//m_rc.right += 184;
	CRenderEngine::DrawImageString(hDC, m_pManager, m_rc, m_rc, (LPCTSTR)m_sBkImage, NULL, NULL);
	Invalidate();
}

void CSliderExUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcsicmp(pstrName, _T("bkimagerect")) == 0) {
		LPTSTR pstr = NULL;
		m_BkImageSize.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
		m_BkImageSize.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
	}
	else if (_tcsicmp(pstrName, _T("invalidrect")) == 0) {
		LPTSTR pstr = NULL;
		m_InvalidSize.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
		m_InvalidSize.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
	}
	else if (_tcsicmp(pstrName, _T("focusedbkcolor")) == 0) {
		if(*pstrValue == _T('#')) 
			pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		m_FocusedBkColor = _tcstoul(pstrValue, &pstr, 16);
	}
	__super::SetAttribute(pstrName, pstrValue);
}
