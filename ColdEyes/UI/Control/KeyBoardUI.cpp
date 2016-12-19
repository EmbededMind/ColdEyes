#include "stdafx.h"
#include "KeyBoardUI.h"

IMPLEMENT_DUICONTROL(CKeyBoardUI)

CDuiString keyValue[4][10] = {
	{_T("1"),_T("2"),_T("3"),_T("4"),_T("5"),_T("6"), _T("7"),_T("8"),_T("9"), _T("0")},
	{_T("a"),_T("b"),_T("c"),_T("d"),_T("e"),_T("f"), _T("g"),_T("h"),_T("i"), _T("") },
	{_T("j"),_T("k"),_T("l"),_T("m"),_T("n"),_T("o"), _T("p"),_T("q"),_T("r"), _T("") },
	{_T("s"),_T("t"),_T("u"),_T("v"),_T("w"),_T("x"), _T("y"),_T("z"),_T(""), _T("") }
};

CKeyBoardUI::CKeyBoardUI()
	:m_focusInx(0)
{
	m_line = 4;
	m_row = 10;
	Layout();
	AddKeyElement();
	SetKeyElementText();
	SetKeyElementTextColor(0,0xFF9B9B9B);
	SetKeyElementTextColor(1, 0xFF4561E3);
	SetKeyElementTextColor(2, 0xFF4561E3);
	SetKeyElementTextColor(3, 0xFF4561E3);
	SetKeyElementFocusedTextColor(0xFFFFFFFF);
}

CKeyBoardUI::CKeyBoardUI(UINT8 line, UINT8 row, CDuiString* pKeyText)
	:m_focusInx(0)
{
	m_line = line;
	m_row = row;
	m_pKeyText = pKeyText;
}

CKeyBoardUI::~CKeyBoardUI()
{
}

void CKeyBoardUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcsicmp(pstrName, _T("itembkimage")) == 0) {
		if (*pstrValue == '#') {
			pstrValue = ::CharNext(pstrValue);
			int line,row;
			LPTSTR pstr = NULL;
			line = _tcstol(pstrValue, &pstr, 10); ASSERT(pstr);
			row = _tcstol(pstr +1, &pstr, 10); ASSERT(pstr);
			pstrValue += 3;
			SetKeyElementBkImage(line, row, pstrValue);
		}
		else {
			SetKeyElementBkImage(pstrValue);
		}
	}
	else if (_tcsicmp(pstrName, _T("itemfocusedimage")) == 0) {
		if (*pstrValue == '#') {
			pstrValue = ::CharNext(pstrValue);
			int line, row;
			LPTSTR pstr = NULL;
			line = _tcstol(pstrValue, &pstr, 10); ASSERT(pstr);
			row = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);
			pstrValue += 3;
			SetKeyElementFocusedImage(line, row, pstrValue);
		}
		else {
			SetKeyElementFocusedImage(pstrValue);
		}
	}
	else if (_tcsicmp(pstrName, _T("itemfont")) == 0){
		SetKeyElementFont(_ttoi(pstrValue));
	}
	__super::SetAttribute(pstrName, pstrValue);
}

void CKeyBoardUI::DoEvent(TEventUI & event)
{
	switch (event.Type) {
	case UIEVENT_KEYDOWN:
		switch (event.wParam) {
			case VK_UP:
				if (m_focusInx > 9) {
					m_focusInx -= 10;
					m_pKeyElement[m_focusInx]->SetFocus();
				}
				break;

			case VK_DOWN:
				if (m_focusInx < (m_line - 1)*m_row) {
					m_focusInx += 10;
					m_pKeyElement[m_focusInx]->SetFocus();

				}
				break;

			case VK_LEFT:
				if (m_focusInx > 0) {
					m_focusInx -= 1;
					m_pKeyElement[m_focusInx]->SetFocus();
				}
				break;

			case VK_RIGHT:
				if (m_focusInx < (m_row*m_line)-1) {
					m_focusInx += 1;
					m_pKeyElement[m_focusInx]->SetFocus();
				}
				break;

			default:
				break;
		}
		break;

	case UIEVENT_SETFOCUS:
		m_pKeyElement[0]->SetFocus();
		break;
	}
	__super::DoEvent(event);
}

void CKeyBoardUI::Layout()
{
	CControlUI* pHead = new CControlUI;
	pHead->SetFixedHeight(27);
	Add(pHead);
	for (int i = 0; i < m_line; i++) {
		CHorizontalLayoutUI* pLayout = new CHorizontalLayoutUI;
		pLayout->SetPadding({ 20,0,0,0 });
		pLayout->SetFixedHeight(67);
		m_pLineLayout.push_back(pLayout);
		Add(m_pLineLayout[i]);
		//m_pChildLayout[i]->SetAttribute(_T("style"), _T("key_board_childlayout"));
	}
}

void CKeyBoardUI::AddKeyElement()
{
	for (int line = 0; line < m_line; line++) {
		for (int row = 0; row < m_row; row++) {
			CButtonUI* pItem = new CButtonUI();
			m_pKeyElement.push_back(pItem);
			pItem->OnEvent += MakeDelegate(this, &CKeyBoardUI::OnKeyClickedListener);
			m_pLineLayout[line]->Add(pItem);
		}
	}
}

void CKeyBoardUI::SetKeyElementText()
{
	for (int line = 0; line < m_line; line++) {
		for (int row = 0; row < m_row; row++) {
			m_pKeyElement[line * 10 + row]->SetText(keyValue[line][row]);
		}
	}
}

void CKeyBoardUI::SetKeyElementText(UINT line, UINT row, CDuiString text)
{

}

void CKeyBoardUI::SetKeyElementBkColor(DWORD Color)
{
	for (int line = 0; line < m_line; line++) {
		for (int row = 0; row < m_row; row++) {
			m_pKeyElement[line * 10 + row]->SetBkColor(Color);
		}
	}
}

void CKeyBoardUI::SetKeyElementBkColor(UINT line, UINT row, DWORD color)
{
}

void CKeyBoardUI::SetKeyElementTextColor(DWORD Color)
{
	for (int line = 0; line < m_line; line++) {
		for (int row = 0; row < m_row; row++) {
			m_pKeyElement[line * 10 + row]->SetTextColor(Color);

		}
	}
}

void CKeyBoardUI::SetKeyElementTextColor(UINT line, DWORD Color)
{
	for (int i = 0; i < m_row; i++) {
		m_pKeyElement[line * 10 + i]->SetTextColor(Color);
	}
}

void CKeyBoardUI::SetKeyElementTextColor(UINT line, UINT row, DWORD Color)
{
	m_pKeyElement[line * 10 + row]->SetTextColor(Color);
}

void CKeyBoardUI::SetKeyElementFocusedBkColor(DWORD Color)
{

}

void CKeyBoardUI::SetKeyElementFocusedBkColor(UINT line, UINT row, DWORD color)
{
}

void CKeyBoardUI::SetKeyElementFocusedTextColor(DWORD Color)
{
	for (int line = 0; line < m_line; line++) {
		for (int row = 0; row < m_row; row++) {
			m_pKeyElement[line * 10 + row]->SetFocusedTextColor(Color);
		}
	}
}

void CKeyBoardUI::SetKeyElementFocusedTextColor(UINT line, UINT row, DWORD Color)
{
	m_pKeyElement[line * 10 + row]->SetFocusedTextColor(Color);
}

void CKeyBoardUI::SetKeyElementBkImage(LPCTSTR image)
{
	for (int line = 0; line < m_line; line++) {
		for (int row = 0; row < m_row; row++) {
			m_pKeyElement[line * 10 + row]->SetBkImage(image);
		}
	}
}

void CKeyBoardUI::SetKeyElementBkImage(UINT line, UINT row, LPCTSTR image)
{
	m_pKeyElement[line * 10 + row]->SetBkImage(image);
}

void CKeyBoardUI::SetKeyElementFocusedImage(LPCTSTR image)
{
	for (int line = 0; line < m_line; line++) {
		for (int row = 0; row < m_row; row++) {
			m_pKeyElement[line * 10 + row]->SetFocusedImage(image);
		}
	}
}

void CKeyBoardUI::SetKeyElementFocusedImage(UINT line, UINT row, LPCTSTR image)
{
	m_pKeyElement[line * 10 + row]->SetFocusedImage(image);
}

void CKeyBoardUI::SetKeyElementFont(int font)
{
	for (int line = 0; line < m_line; line++) {
		for (int row = 0; row < m_row; row++) {
			m_pKeyElement[line * 10 + row]->SetFont(font);
		}
	}
}

void CKeyBoardUI::SetShowStringControl(CControlUI * pControl)
{
	m_pShowControl = pControl;
}

void CKeyBoardUI::SetShowStringControlText(CDuiString text)
{
	CDuiString oldText;
	oldText = m_pShowControl->GetText();
	if ((m_pShowControl->GetText().GetLength()) < 32) {
		oldText.Append(text);
		m_pShowControl->SetText(oldText);
	}
	else {
		//CMsgWnd::MessageBox(m_pManager->GetPaintWindow(), _T("mb_shipname_input.xml"), NULL, NULL, NULL, NULL);
	}
}

bool CKeyBoardUI::OnKeyClickedListener(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CButtonUI* pSender = (CButtonUI*)pMsg->pSender;
	CDuiString text = pSender->GetText();
	switch (pMsg->Type) {
	case UIEVENT_BUTTONDOWN:
		if (!text.IsEmpty()) {
			SetShowStringControlText(text);
		}
		else {
			if (pSender == m_pKeyElement[38]) {
				CDuiString oldText = m_pShowControl->GetText();
				if (oldText.GetLength() > 0) {
					oldText.Assign(oldText, oldText.GetLength() - 1);
					m_pShowControl->SetText(oldText);
				}
			}
			else {
				m_pShowControl->SetText(_T(""));
			}
		}
		break;

	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			break;

		case VK_DOWN:
			break;

		case VK_LEFT:
			break;

		case VK_RIGHT:
			break;
		case VK_RETURN:
			if (!text.IsEmpty()) {
				SetShowStringControlText(text);
			}
			else {
				if (pSender == m_pKeyElement[38]) {
					CDuiString oldText = m_pShowControl->GetText();
					if (oldText.GetLength() > 0) {
						oldText.Assign(oldText, oldText.GetLength() - 1);
						m_pShowControl->SetText(oldText);
					}
				}
				else {
					m_pShowControl->SetText(_T(""));
				}
			}
			break;
		case VK_BACK:
			break;
		default:
			break;
		}
		break;
	default:
		__super::DoEvent(*pMsg);
		break;
	}
	return true;
}




