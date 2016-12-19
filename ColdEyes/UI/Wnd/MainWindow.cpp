#include "stdafx.h"
#include "MainWindow.h"




LPCTSTR  CMainWindow::GetWindowClassName() const
{
	return _T("MainWindow");
}


CDuiString CMainWindow::GetSkinFolder()
{
	return _T("skin");
}


CDuiString CMainWindow::GetSkinFile()
{
	return _T("main_window.xml");
}



void  CMainWindow::InitWindow()
{
//	CButtonUI* pBtn  = (CButtonUI*)m_pm.FindControl(_T("test"));
}



