#include "stdafx.h"
#include "TimeSpanPickerUI.h"
#include "Shlwapi.h"

IMPLEMENT_DUICONTROL(CTimeSpanPickerUI)


CTimeSpanPickerUI::CTimeSpanPickerUI()
{
	pBeginHour = new CButtonUI();
	pBeginMinute = new CButtonUI();
	pEndHour = new CButtonUI();
	pEndMinute = new CButtonUI();

	pBeginHour->OnEvent += MakeDelegate(this, &CTimeSpanPickerUI::OnBeginHourLister);
	pBeginMinute->OnEvent += MakeDelegate(this, &CTimeSpanPickerUI::OnBeginMinuteLister);
	pEndHour->OnEvent += MakeDelegate(this, &CTimeSpanPickerUI::OnEndHourLister);
	pEndMinute->OnEvent += MakeDelegate(this, &CTimeSpanPickerUI::OnEndMinuteLister);
	
	pLabel[0] = new CLabelUI;
	pLabel[1] = new CLabelUI;
	pLabel[2] = new CLabelUI;

	Add(pBeginHour);
	Add(pLabel[0]);
	Add(pBeginMinute);
	Add(pLabel[1]);
	Add(pEndHour);
	Add(pLabel[2]);
	Add(pEndMinute);

	pLabel[0]->SetText(_T(":"));
	pLabel[2]->SetText(_T(":"));
	pLabel[0]->SetFixedWidth(17);
	pLabel[2]->SetFixedWidth(17);

	pBeginHour->SetTextStyle(DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	pBeginMinute->SetTextStyle(DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	pEndHour->SetTextStyle(DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	pEndMinute->SetTextStyle(DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	pLabel[0]->SetTextStyle(DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	pLabel[1]->SetBkColor(0xFF9B9B9B);
	pLabel[2]->SetTextStyle(DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	pLabel[1]->SetFixedWidth(200);
	pLabel[1]->SetFixedHeight(10);
	pLabel[1]->SetPadding({42,82,42,0});

	pBeginHour->SetText(_T("20"));
	pBeginMinute->SetText(_T("20"));
	pEndHour->SetText(_T("20"));
}

CTimeSpanPickerUI::~CTimeSpanPickerUI()
{
	
}

void CTimeSpanPickerUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	if (_tcsicmp(pstrName, _T("itemfocusedimage")) == 0){
		pBeginHour->SetFocusedImage(pstrValue);
		pEndHour->SetFocusedImage(pstrValue);
		pBeginMinute->SetFocusedImage(pstrValue);
		pEndMinute->SetFocusedImage(pstrValue);
	}
	else if (_tcsicmp(pstrName, _T("itemfont")) == 0) {
		pBeginHour->SetFont(_ttoi(pstrValue));
		pEndHour->SetFont(_ttoi(pstrValue));
		pBeginMinute->SetFont(_ttoi(pstrValue));
		pEndMinute->SetFont(_ttoi(pstrValue));
		pLabel[0]->SetFont(_ttoi(pstrValue));
		pLabel[2]->SetFont(_ttoi(pstrValue));
	}
	else if (_tcsicmp(pstrName, _T("focusedtextcolor")) == 0) {
		if (*pstrValue == _T('#')) 
			pstrValue = ::CharNext(pstrValue);
		LPTSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);

		pBeginHour->SetFocusedTextColor(clrColor);
		pEndHour->SetFocusedTextColor(clrColor);
		pBeginMinute->SetFocusedTextColor(clrColor);
		pEndMinute->SetFocusedTextColor(clrColor);
	}
	__super::SetAttribute(pstrName,pstrValue);
}

void CTimeSpanPickerUI::DoEvent(TEventUI & event)
{
	switch (event.Type) {
	case UIEVENT_KEYDOWN:
		mFocusedIndex = GetItemIndex(m_pManager->GetFocus());
		switch (event.wParam) {
		case VK_LEFT:
			if (mFocusedIndex > 0) {
				mFocusedIndex -= 2;
				GetItemAt(mFocusedIndex)->SetFocus();
			}
			break;

		case VK_RIGHT:
			if (mFocusedIndex < GetCount() - 1) {
				mFocusedIndex += 2;
				GetItemAt(mFocusedIndex)->SetFocus();
			}
			break;
		}
		break;

	}

	__super::DoEvent(event);
}


bool CTimeSpanPickerUI::OnBeginHourLister(void * param)
{
	int val;
	CDuiString text;
	TEventUI* uMsg = (TEventUI*)param;
	if (uMsg->Type == UIEVENT_KEYDOWN) {
		switch (uMsg->wParam) {
		case VK_UP:
			val = IncreaseHour(pBeginHour);
			text.Format(_T("%02d"), val);
			pBeginHour->SetText(text);

			UpdateTime();
			break;

		case VK_DOWN:
			val = DecreaseHour(pBeginHour);
			text.Format(_T("%02d"), val);
			pBeginHour->SetText(text);

			UpdateTime();
			break;
		}
	}
	return true;
}

bool CTimeSpanPickerUI::OnBeginMinuteLister(void * param)
{
	int val;
	CDuiString text;
	TEventUI* uMsg = (TEventUI*)param;
	if (uMsg->Type == UIEVENT_KEYDOWN) {
		switch (uMsg->wParam) {
		case VK_UP:
			val = IncreaseMinute(pBeginMinute);
			text.Format(_T("%02d"), val);
			pBeginMinute->SetText(text);

			UpdateTime();
			break;

		case VK_DOWN:
			val = DecreaseMinute(pBeginMinute);
			text.Format(_T("%02d"), val);
			pBeginMinute->SetText(text);

			UpdateTime();
			break;
		}
	}
	return true;
}

bool CTimeSpanPickerUI::OnEndHourLister(void * param)
{
	int val;
	CDuiString text;
	TEventUI* uMsg = (TEventUI*)param;
	if (uMsg->Type == UIEVENT_KEYDOWN) {
		switch (uMsg->wParam) {
		case VK_UP:
			val = IncreaseHour(pEndHour);
			text.Format(_T("%02d"), val);
			pEndHour->SetText(text);

			UpdateTime();
			break;

		case VK_DOWN:
			val = DecreaseHour(pEndHour);
			text.Format(_T("%02d"), val);
			pEndHour->SetText(text);

			UpdateTime();
			break;
		}
	}
	return true;
}

bool CTimeSpanPickerUI::OnEndMinuteLister(void * param)
{
	int val;
	CDuiString text;
	TEventUI* uMsg = (TEventUI*)param;
	if (uMsg->Type == UIEVENT_KEYDOWN) {
		switch (uMsg->wParam) {
		case VK_UP:
			val = IncreaseMinute(pEndMinute);
			text.Format(_T("%02d"), val);
			pEndMinute->SetText(text);

			UpdateTime();
			break;

		case VK_DOWN:
			val = DecreaseMinute(pEndMinute);
			text.Format(_T("%02d"), val);
			pEndMinute->SetText(text);

			UpdateTime();
			break;
		}
	}
	return true;
}

int CTimeSpanPickerUI::DecreaseHour(CButtonUI* Item)
{
	int val;
	CDuiString text = Item->GetText();
	val = StrToInt(text);

	if (val > 0) {
		val--;
	}
	else {
		val = 23;
	}
	return val;
}

int CTimeSpanPickerUI::DecreaseMinute(CButtonUI* Item)
{
	int val;
	CDuiString text = Item->GetText();
	val = StrToInt(text);
	if (val > 9) {
		val = (val / 10) * 10;
		val -= 10;
	}
	else {
		val = 50;
	}
	return val;
}

int CTimeSpanPickerUI::IncreaseHour(CButtonUI* Item)
{
	int val;
	CDuiString text = Item->GetText();
	val = StrToInt(text);

	if (val < 23) {
		val++;
	}
	else {
		val = 0;
	}
	return val;
}

int CTimeSpanPickerUI::IncreaseMinute(CButtonUI* Item)
{
	int val;
	CDuiString text = Item->GetText();
	val = StrToInt(text);
	if (val <49) {
		val = (val / 10) * 10;
		val += 10;
	}
	else {
		val = 0;
	}
	return val;
}

void CTimeSpanPickerUI::UpdateTime()
{
	int hour1, hour2, minute1, minute2;
	hour1 = StrToInt(pBeginHour->GetText());
	hour2 = StrToInt(pEndHour->GetText());
	minute1 = StrToInt(pBeginMinute->GetText());
	minute2 = StrToInt(pEndMinute->GetText());

	tBegin = hour1 * 60 + minute1;
	tEnd = hour2 * 60 + minute2;
}

void CTimeSpanPickerUI::SetTime(DWORD beginTime, DWORD endTime)
{
	tBegin = beginTime;
	tEnd = endTime;

	CDuiString text;
	if (beginTime < 1440 && endTime < 1440) {
		text.Format(_T("%02d"), beginTime / 60);
		pBeginHour->SetText(text);

		text.Format(_T("%02d"), endTime / 60);
		pEndHour->SetText(text);

		text.Format(_T("%02d"), beginTime % 60);
		pBeginMinute->SetText(text);

		text.Format(_T("%02d"), endTime % 60);
		pEndMinute->SetText(text);
	}
}

void CTimeSpanPickerUI::GetTime(DWORD * pBegining, DWORD * pEnd)
{
	*pBegining = tBegin;
	*pEnd = tEnd;
}

