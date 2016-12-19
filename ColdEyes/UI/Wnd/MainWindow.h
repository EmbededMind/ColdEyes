#pragma once

#include "DuiLib\UIlib.h"

using namespace DuiLib;

class CMainWindow
	:public WindowImplBase
{
	
	virtual LPCTSTR		GetWindowClassName() const;

	virtual CDuiString  GetSkinFolder();
	virtual CDuiString	GetSkinFile();

	virtual void		InitWindow();

	bool                Test(void*);
};
