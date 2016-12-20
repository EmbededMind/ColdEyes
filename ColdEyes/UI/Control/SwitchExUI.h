#pragma once

#include "DuiLib\UIlib.h"
using namespace DuiLib;

class CSwitchExUI : public CButtonUI
{
DECLARE_DUICONTROL(CSwitchExUI)
public:
	CSwitchExUI();
	~CSwitchExUI();
	void DoEvent(TEventUI &event);
	void PaintStatusImage(HDC hDC);
	void SetValue(bool value);
	bool GetValue();
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void SetOnImage(CDuiString pstrValue);
	void SetOffImage(CDuiString pstrValue);

private:
	bool mValue;
	CDuiString sOnImage;
	CDuiString sOffImage;
};
