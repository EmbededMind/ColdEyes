#pragma once

#include "DuiLib\UIlib.h"


using namespace DuiLib;

class CTimeSpanPickerUI
	:public CHorizontalLayoutUI
{
DECLARE_DUICONTROL(CTimeSpanPickerUI)

	CTimeSpanPickerUI();
	~CTimeSpanPickerUI();
	virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	virtual void DoEvent(TEventUI& event);

	//Item Delegate 
	bool OnBeginHourLister(void* param);
	bool OnBeginMinuteLister(void* param);
	bool OnEndHourLister(void* param);
	bool OnEndMinuteLister(void* param);

	int DecreaseHour(CButtonUI*);
	int  DecreaseMinute(CButtonUI*);
	int IncreaseHour(CButtonUI*);
	int IncreaseMinute(CButtonUI*);
	void UpdateTime();

	void ShowOnwerLable();

	void SetTime(DWORD beginTime, DWORD endTime);
	void GetTime(DWORD* pBegining, DWORD* pEnd);

	template <class O, class T>
	void ItemMakeDelegate(O* pObject, bool (T::* pFn)(void*))
	{
		pBeginHour->OnEvent += MakeDelegate(pObject, pFn);
		pEndHour->OnEvent += MakeDelegate(pObject, pFn);
		pBeginMinute->OnEvent += MakeDelegate(pObject, pFn);
		pEndMinute->OnEvent += MakeDelegate(pObject, pFn);
	}

private:
	int mFocusedIndex;

	DWORD tBegin;
	DWORD tEnd;


	CButtonUI* pBeginHour;
	CButtonUI* pEndHour;

	CButtonUI* pBeginMinute;
	CButtonUI* pEndMinute;

	CLabelUI* pLabel[3];


	LPCTSTR focusedImage;

};
