#include "stdafx.h"
#include "MyMenuWnd.h"
#include "conio.h"


CMyMenuWnd::CMyMenuWnd()
{
}

CMyMenuWnd::~CMyMenuWnd()
{
}


LPCTSTR CMyMenuWnd::GetWindowClassName() const
{
	return _T("MenuWnd");
}

CDuiString CMyMenuWnd::GetSkinFile()
{
	return _T("MenuUI.xml");
}

void CMyMenuWnd::Notify(TNotifyUI& msg)
{

}



LRESULT CMyMenuWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

// UI Init 
void CMyMenuWnd::InitWindow()
{
	//CKeyBoardUI* pLayout =static_cast<CKeyBoardUI*> (m_pm.FindControl(_T("keyboard")));
	//pLayout->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnLayoutDoEventTest);
	//LayoutInit();
	InitMenuItem();

	//°ó¶¨´¬Ãû±à¼­¿òµÄÊäÈë¼üÅÌ
	static_cast<CKeyBoardUI*>(m_pm.FindControl(kKeyboardName))->SetShowStringControl(m_pm.FindControl(kEditCtlHostNameName)); 

	MakeItemsDelegate();
}

void CMyMenuWnd::InitMenuItem()
{
	//Host Set
	SetSubMenuParent(kSubMenuItemHostName, kMenuItemHostSetName);
	SetSubMenuParent(kSubMenuItemSysSetName,kMenuItemHostSetName);

	//Auot Watch
	SetSubMenuParent(kSubMenuItemAwTimeName, kMenuItemAutoWatchName);
	SetSubMenuParent(kSubMenuItemAlarmVoiceName, kMenuItemAutoWatchName);
	SetSubMenuParent(kSubMenuItemAlarmLightName, kMenuItemAutoWatchName);
	SetSubMenuParent(kSubMenuItemAwOnOffRecordName, kMenuItemAutoWatchName);
}

void CMyMenuWnd::LayoutInit()
{
	AddLayout(_T("HostName.xml"), (CContainerUI*)m_pm.FindControl(kBodyLayoutHostSetName));
	AddLayout(_T("SysSet.xml"), (CContainerUI*)m_pm.FindControl(kBodyLayoutHostSetName));

	AddLayout(_T("AwTime.xml"), (CContainerUI*)m_pm.FindControl(kBodyLayoutAwTime));
	AddLayout(_T("AlarmVoice.xml"), (CContainerUI*)m_pm.FindControl(kBodyLayoutAwTime));
	AddLayout(_T("AlarmLights.xml"), (CContainerUI*)m_pm.FindControl(kBodyLayoutAwTime));
	AddLayout(_T("AwOnOffRecords.xml"), (CContainerUI*)m_pm.FindControl(kBodyLayoutAwTime));
	//AddLayout(_T(""))
}

void CMyMenuWnd::AddLayout(LPCTSTR xmlName, CContainerUI* ParentLayout)
{
	CDialogBuilder Builder;
	ParentLayout->Add((CContainerUI*)Builder.Create(xmlName, NULL, this, &m_pm, NULL));
}

void CMyMenuWnd::AddAtLayout(LPCTSTR xmlName, CContainerUI* ParentLayout, UINT8 inx)
{
	CDialogBuilder Builder;
	ParentLayout->AddAt((CContainerUI*)Builder.Create(xmlName, NULL, this, &m_pm, NULL),inx);
}

void CMyMenuWnd::SetSubMenuParent(LPCTSTR sSubMenuName, LPCTSTR sParentName)
{
	
	if (m_pm.FindControl(sSubMenuName)) {
		static_cast<CSubMenuItemUI*>(m_pm.FindControl(sSubMenuName))->SetParentMenuItem(sParentName);
	}
}

void CMyMenuWnd::MakeItemsDelegate()
{
	SubMenuMakeDelegate(kSubMenuItemHostName);
	SubMenuMakeDelegate(kSubMenuItemSysSetName);
	SubMenuMakeDelegate(kSubMenuItemAwTimeName);
	SubMenuMakeDelegate(kSubMenuItemAlarmVoiceName);
	SubMenuMakeDelegate(kSubMenuItemAlarmLightName);
	SubMenuMakeDelegate(kSubMenuItemAwOnOffRecordName);

}

void CMyMenuWnd::SubMenuMakeDelegate(const TCHAR* const Name)
{
	static_cast<CSubMenuItemUI*>(m_pm.FindControl(Name))->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnSubMenuItem);
}


// Delegate Function
bool CMyMenuWnd::OnSubMenuItem(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CSubMenuItemUI* item = (CSubMenuItemUI*)pMsg->pSender;
	CDuiString Name = item->GetName();
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_BACK:
			if (item->GetParentItem())
				item->GetParentItem()->SetFocus();
			break;

		case VK_RIGHT:
			if (_tcsicmp(Name, kSubMenuItemHostName) == 0) {

			}
			else if (_tcsicmp(Name, kSubMenuItemSysSetName) == 0) {

			}
			else if (_tcsicmp(Name, kSubMenuItemAwTimeName) == 0) {

			}
			else if (_tcsicmp(Name, kSubMenuItemAlarmVoiceName) == 0) {

			}
			else if (_tcsicmp(Name, kSubMenuItemAlarmLightName) == 0) {

			}
			else if (_tcsicmp(Name, kSubMenuItemAwOnOffRecordName) == 0) {

			}
			return false;
			break;

		}
		break;
	}
	return true;
}


// SubMenuItem Add Or Delete
void CMyMenuWnd::AddAlarmMenuItem()
{

}

void CMyMenuWnd::AddVideoObtainMenuItem()
{

}

void CMyMenuWnd::AddPortConfigMenuItem()
{

}

void CMyMenuWnd::DeleteAlarmMenuItem()
{
}

void CMyMenuWnd::DeleteVideoObtainMenuItem()
{
}

void CMyMenuWnd::DeletePortConfigMenuItem()
{
}


//bool CMyMenuWnd::OnLayoutDoEventTest(void * param)
//{
//	TEventUI* pMsg = (TEventUI*)param;
//
//	if (pMsg->Type == UIEVENT_KEYDOWN) {
//		Print("GG ---------");
//	}
//	return false;
//}
