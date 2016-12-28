#pragma once

#include "DuiLib\UIlib.h"
using namespace DuiLib;

class CEditExUI : public CButtonUI
{
DECLARE_DUICONTROL(CEditExUI)
public:
	CEditExUI();
	~CEditExUI();
	void DoEvent(TEventUI &event);
	virtual void PaintBorder(HDC hDC);

	void SetName(CString);
	void SetStatus(bool newStatus);
	bool GetStatus();

private:
	bool isEditing;
	DWORD m_sBorderColor;
};

