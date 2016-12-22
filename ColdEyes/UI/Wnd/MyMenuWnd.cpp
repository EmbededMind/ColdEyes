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
	if (msg.sType == DUI_MSGTYPE_KILLFOCUS) {
		FocusedItemClassName = msg.pSender->GetClass();
		pKillFocsedItem = msg.pSender;

	}

	if (msg.sType == DUI_MSGTYPE_SETFOCUS) {
		if (FocusedItemClassName != msg.pSender->GetClass()) {
			//焦点在一级模块
			if (_tcsicmp(msg.pSender->GetClass(), _T("MenuItemUI")) == 0) {
				Print("MenuItem");
				if (pKillFocsedItem) {
					((CMenuItemUI*)pKillFocsedItem)->SetStatus(0);
				}
				((CMenuItemUI*)msg.pSender)->SetStatus(0);
				UpdataBkColor(0,LAYOUT_MENUITEM_FOCUSED, LAYOUT_SUB_NOFOCUS);
			}
			//焦点在二级模块
			else if (_tcsicmp(msg.pSender->GetClass(), _T("SubMenuItemUI")) == 0) {
				Print("SubMenuItem");
				if (_tcsicmp(FocusedItemClassName, _T("MenuItemUI")) == 0) {
					((CMenuItemUI*)pKillFocsedItem)->SetStatus(1);
				}
				((CSubMenuItemUI*)msg.pSender)->SetStatus(0);
				UpdataBkColor(0,LAYOUT_SUB_NOFOCUS, LAYOUT_MENUITEM_FOCUSED);
			}
			//焦点在三级模块
			else {
				if (_tcsicmp(FocusedItemClassName, _T("SubMenuItemUI")) == 0) {
					((CMenuItemUI*)pKillFocsedItem)->SetStatus(1);
					UpdataBkColor(1, LAYOUT_BODY_FOCUSED, LAYOUT_SUB_SEL_NOFOCUS);
				}
			}
		}
	}
}



LRESULT CMyMenuWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

void CMyMenuWnd::InitWindow()
{
	MakeItemsDelegate();
}

void CMyMenuWnd::UpdataBkColor(int focusLevel,DWORD Color1,DWORD Color2)
{ 
	int index;
	CButtonUI* pItem;
	CContainerUI* pLayout;	
	
	//二级模块
	CTabLayoutUI* pTabLayout = static_cast<CTabLayoutUI*>(m_pm.FindControl(kLayoutChildrenMenuName));
	pLayout = (CContainerUI*)pTabLayout->GetItemAt(pTabLayout->GetCurSel());	

	pLayout = (CContainerUI*)pLayout->GetItemAt(0);
	pLayout->SetBkColor(Color2);				//布局颜色
	for (int i = 0; i < pLayout->GetCount(); i += 2) {		//控件颜色
		pItem = (CButtonUI*)pLayout->GetItemAt(i);
		pItem->SetBkColor(Color2);
	}

	//焦点在一级模块
	if (focusLevel == 0) {
		pLayout = (CContainerUI*)m_pm.FindControl(KLayoutParentMenuName);
		pLayout->SetBkColor(Color1);			//布局颜色
		for (int i = 0; i < pLayout->GetCount(); i += 2) {		//控件颜色
			pItem = (CButtonUI*)pLayout->GetItemAt(i);
			pItem->SetBkColor(Color1);
		}
	}	
	//焦点在三级模块
	else if (focusLevel == 1) {
		pTabLayout = static_cast<CTabLayoutUI*>(m_pm.FindControl(kLayoutChildrenMenuName));
		pLayout = (CContainerUI*)pTabLayout->GetItemAt(pTabLayout->GetCurSel());
		pTabLayout = (CTabLayoutUI*)pLayout->GetItemAt(1);
		pLayout = (CContainerUI*)pTabLayout->GetItemAt(pTabLayout->GetCurSel());
		pLayout->SetBkColor(LAYOUT_BODY_FOCUSED);
	}

}

void CMyMenuWnd::MakeItemsDelegate()
{
	MenuItemMakeDelegate(KMenuItemHomeWatchName);

	SubMenuMakeDelegate(kSubMenuItemHostName);
	SubMenuMakeDelegate(kSubMenuItemSysSetName);
	SubMenuMakeDelegate(kSubMenuItemAwTimeName);
	SubMenuMakeDelegate(kSubMenuItemAlarmVoiceName);
	SubMenuMakeDelegate(kSubMenuItemAlarmLightName);
	SubMenuMakeDelegate(kSubMenuItemAwOnOffRecordName);

	m_pm.FindControl(kEditCtlHostNameName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnHostName);

	m_pm.FindControl(kSysBrightName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnSysBrightness);
	m_pm.FindControl(kSysVolumeName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnSysVolume);
	m_pm.FindControl(kSysVersionName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnSysVersion);
	m_pm.FindControl(kSysFactoryName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnFactorySet);
	m_pm.FindControl(kSysHostModelName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnSysHostModel);
	m_pm.FindControl(kSysSerialNumberName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnSysSerialNumber);

	((CTimeSpanPickerUI*)m_pm.FindControl(kTimeSpanPickerAwName))->ItemMakeDelegate(this, &CMyMenuWnd::OnAwTime);
	m_pm.FindControl(kSwitchAlarmVoiceName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnAlarmVoiceSwitch);
	m_pm.FindControl(kOptionAlarmVoiceDefaultName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnAlarmVoiceOption);
	m_pm.FindControl(kBtAlarmVoiceRecordName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnAlarmVoiceRecord);
	m_pm.FindControl(kAlarmLightName)->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnAlarmLight);
}

void CMyMenuWnd::MenuItemMakeDelegate(const TCHAR* const Name)
{
	static_cast<CMenuItemUI*>(m_pm.FindControl(Name))->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnMenuItem);
}

void CMyMenuWnd::SubMenuMakeDelegate(const TCHAR* const Name)
{
	static_cast<CSubMenuItemUI*>(m_pm.FindControl(Name))->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnSubMenuItem);
}


bool CMyMenuWnd::OnMenuItem(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CMenuItemUI* Item = (CMenuItemUI*)pMsg->pSender;

	if (pMsg->Type == UIEVENT_KEYDOWN) {
		if (pMsg->wParam == VK_RIGHT) {
			if (_tcscmp(Item->GetName(), KMenuItemHomeWatchName) == 0) {

				return false;
			}
		}
	}
	return true;
}

/*************** Delegate Functions*********************/
bool CMyMenuWnd::OnSubMenuItem(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CSubMenuItemUI* pItem = (CSubMenuItemUI*)pMsg->pSender;
	CDuiString Name = pItem->GetName();
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_BACK:
			if (pItem->GetOnwerMenuItemName()) {
				m_pm.FindControl(pItem->GetOnwerMenuItemName())->SetFocus();
			}
			break;
		//----------------------------------------------
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

bool CMyMenuWnd::OnHostName(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CEditExUI* Item = (CEditExUI*)pMsg->pSender;
	switch (pMsg->Type){
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_BACK:
			m_pm.FindControl(kSubMenuItemHostName)->SetFocus();
			break;
		//------------------------------
		case VK_RETURN:
			Item->SetStatus(true);
			m_pm.FindControl(kKeyboardName)->SetVisible(true);
			m_pm.FindControl(kKeyboardName)->SetFocus();
			m_pm.FindControl(kLayoutPromptName)->SetVisible(true);
			break;
		}
		break;
	//----------------------------------------------
	case UIEVENT_SETFOCUS:
		Item->SetStatus(false);
		if (m_pm.FindControl(kKeyboardName)->IsVisible()) {
			m_pm.FindControl(kKeyboardName)->SetVisible(false);
			m_pm.FindControl(kLayoutPromptName)->SetVisible(false);
		}
		break;
	}


	return true;
}

bool CMyMenuWnd::OnAlarmFileList(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;

	return false;
}

bool CMyMenuWnd::OnNormalFileList(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	return false;
}

bool CMyMenuWnd::OnCameraName(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam){
		case VK_BACK:
			/*if(cameraname is change){
				if(ok==messagebox()){
					save
				}
				else{
					
				}
			}*/

			//SetFocus to submenuItem
			break;
		//----------------------------------------------
		case VK_DOWN:
			//SetFocus to camera switch
			break;
		}
		break;
	}
	return false;
}

bool CMyMenuWnd::OnCameraVolume(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CSliderExUI* pItem = (CSliderExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			//setfocus to camera switch
			break;
		//----------------------------------------------
		case VK_LEFT:
			if (pItem->GetValue() > pItem->GetMinValue()) {
				pItem->SetValue(pItem->GetValue() - 1);
				//save();
			}
			break;
		//----------------------------------------------
		case VK_RIGHT:
			if (pItem->GetValue() < pItem->GetMaxValue()) {
				pItem->SetValue(pItem->GetValue() + 1);
				// save
			}
			break;
		//----------------------------------------------
		case VK_DOWN:
			//setfocus to videoSave
			break;
		//----------------------------------------------
		case VK_BACK:
			/*
			if(cameraname is change){
				if(idok==messagebox()){
					save()
				}
				else{

				}
			}
			setfocus to submenuitem
			*/
			break;
		}

		return false;
		break;
	}

	return true;
}

bool CMyMenuWnd::OnCameraSwitch(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CSwitchExUI* pItem = (CSwitchExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			//setfocus to cameraname
			break;

		case VK_DOWN:
			//setfocus to camera volume
			break;

		case VK_BACK:
			/*
			if(cameraname is change){
				if(idok==messagebox()){
					save()
				}
				else{

				}
			}
			setfocus to submenuitem
			*/
			break;

		case VK_LEFT:
			if (pItem->GetValue() == true) {
				/*if(id==messagebox()){
					pItem->SetValue(false);
					pItem->invalidate();
					save();
				}
				*/
			}
			break;

		case VK_RIGHT:
			if (pItem->GetValue() == false) {
				pItem->SetValue(true);
				pItem->Invalidate();
				//save();
			}
			break;
		}
		
		return false;
		break;
	}
	return false;
}

bool CMyMenuWnd::OnCameraStore(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			//setfocus to camera volume
			break;

		//----------------------------------------------
		case VK_DOWN:
			//setfocus to camera aw
			break;
		//----------------------------------------------
		case VK_BACK:
			/*
			if(cameraname is change){
				if(idok==messagebox()){
					save()
				}
				else{

				}
			}
			setfocus to submenuitem
			*/
			break;
		}

		return false;

		break;
	}
	return false;
}

bool CMyMenuWnd::OnCameraAutoWatch(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CLabelExUI* pItem = (CLabelExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			//setfocus to video save
			break;
		//----------------------------------------------
		case VK_RETURN:
			if (!pItem->GetValue()) {
				pItem->SetValue(true);
				pItem->Invalidate();
				//save();
			}
			else {
				/*
				if(idok==messagebox()){
					pItem->SetValue(false);
					pItem->invalidate();
					save();
				}
				*/
			}
			break;
		//----------------------------------------------
		case VK_BACK:
			/*
			if(cameraname is change){
				if(idok==messagebox()){
					save()
				}
				else{
				
				}
			}
			setfocus to submenuitem
			*/
			break;
		}

		return false;

		break;
	}
	return false;
}


bool CMyMenuWnd::OnSysBrightness(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CSliderExUI* pItem = (CSliderExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_LEFT:
			if (pItem->GetValue() > pItem->GetMinValue()) {
				pItem->SetValue(pItem->GetValue() - 1);
			}
			break;
		//----------------------------------------------
		case VK_RIGHT:
			if (pItem->GetValue() < pItem->GetMaxValue()) {
				pItem->SetValue(pItem->GetValue() + 1);
			}
			break;
		//----------------------------------------------
		case VK_DOWN:
			//setfocus to sysset voice
			break;
		//----------------------------------------------
		case VK_BACK:
			break;
		}

		return false;
		break;
	}
	return true;
}

bool CMyMenuWnd::OnSysVolume(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CSliderExUI* pItem = (CSliderExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			//setfocus to sysset brightness
			break;
		//----------------------------------------------
		case VK_LEFT:
			if (pItem->GetValue() > pItem->GetMinValue()) {
				pItem->SetValue(pItem->GetValue() - 1);
			}
			break;
		//----------------------------------------------
		case VK_RIGHT:
			if (pItem->GetValue() < pItem->GetMaxValue()) {
				pItem->SetValue(pItem->GetValue() + 1);
			}
			break;
		//----------------------------------------------
		case VK_DOWN:
			m_pm.FindControl(kSysVersionName)->SetFocus();
			break;
		//----------------------------------------------
		case VK_BACK:
			/*
			if(volume is change){
				if(idok==messagebox()){
					save()
				}
				else{

				}
			}
			*/
			m_pm.FindControl(kSubMenuItemSysSetName)->SetFocus();
			break;
		}

		return false;
		break;
	}
	return true;
}

bool CMyMenuWnd::OnSysVersion(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CLabelExUI* pItem = (CLabelExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			m_pm.FindControl(kSysVolumeName)->SetFocus();
			break;
		//----------------------------------------------
		case VK_DOWN:
			m_pm.FindControl(kSysFactoryName)->SetFocus();
			break;
		//----------------------------------------------
		case VK_BACK:
			/*
			if(volume is change){
			if(idok==messagebox()){
			save()
			}
			else{

			}
			}
			*/
			m_pm.FindControl(kSubMenuItemSysSetName)->SetFocus();
			break;
		//----------------------------------------------
		}

		return false;
		break;
	}
	return true;
}

bool CMyMenuWnd::OnFactorySet(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CLabelExUI* pItem = (CLabelExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			m_pm.FindControl(kSysVersionName)->SetFocus();
			break;
			//----------------------------------------------
		case VK_DOWN:
			//setfocus to factory set
			m_pm.FindControl(kSysHostModelName)->SetFocus();;
			break;
			//----------------------------------------------
		case VK_BACK:
			/*
			if(volume is change){
				if(idok==messagebox()){
					save()
				}
				else{

				}
			}
			*/
			m_pm.FindControl(kSubMenuItemSysSetName)->SetFocus();
			break;
			//----------------------------------------------
		}

		return false;
		break;
	}
	return true;
}

bool CMyMenuWnd::OnSysHostModel(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CLabelExUI* pItem = (CLabelExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			m_pm.FindControl(kSysFactoryName)->SetFocus();
			break;
			//----------------------------------------------
		case VK_DOWN:
			m_pm.FindControl(kSysSerialNumberName)->SetFocus();;
			break;
			//----------------------------------------------
		case VK_BACK:
			/*
			if(volume is change){
			if(idok==messagebox()){
			save()
			}
			else{

			}
			}
			*/
			m_pm.FindControl(kSubMenuItemSysSetName)->SetFocus();
			break;
			//----------------------------------------------
		}

		return false;
		break;
	}
	return true;
}

bool CMyMenuWnd::OnSysSerialNumber(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CLabelExUI* pItem = (CLabelExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			m_pm.FindControl(kSysHostModelName)->SetFocus();
			break;
			//----------------------------------------------
		case VK_BACK:
			/*
			if(volume is change){
			if(idok==messagebox()){
			save()
			}
			else{

			}
			}
			*/
			m_pm.FindControl(kSubMenuItemSysSetName)->SetFocus();
			break;
			//----------------------------------------------
		}

		return false;
		break;
	}
	return true;
}


bool CMyMenuWnd::OnAwTime(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_BACK:
			/*
			if(time is change){
				if(idok==messagebox()){
					save();
				}
			}
			*/
			m_pm.FindControl(kSubMenuItemAwTimeName)->SetFocus();
			break;
		}
		break;

		return false;
	}
	return true;
}

bool CMyMenuWnd::OnAlarmVoiceSwitch(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CSwitchExUI* pItem = (CSwitchExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_LEFT:
			if (pItem->GetValue()) {
				pItem->SetValue(false);
				pItem->Invalidate();
			}
			break;
		//----------------------------------------------
		case VK_RIGHT:
			if (!pItem->GetValue()) {
				pItem->SetValue(true);
				pItem->Invalidate();
			}
			break;
		//----------------------------------------------
		case VK_BACK:
			/*
			if(voice Sets is change){
				if(idok==messagebox()){
					save();
				}
			}
			*/
			m_pm.FindControl(kSubMenuItemAlarmVoiceName)->SetFocus();
			break;
		//----------------------------------------------
		case VK_DOWN:
			m_pm.FindControl(kOptionAlarmVoiceDefaultName)->SetFocus();
			break;
		}
		break;

		return false;
	}
	return true;
}

bool CMyMenuWnd::OnAlarmVoiceOption(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	COptionExUI* pItem = (COptionExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			if (_tcscmp(pItem->GetName(),kOptionAlarmVoiceDefaultName)==0) {
				m_pm.FindControl(kSwitchAlarmVoiceName)->SetFocus();
			}
			else {
				m_pm.FindControl(kOptionAlarmVoiceDefaultName)->SetFocus();
			}
			break;
		//----------------------------------------------
		case VK_DOWN:
			if (_tcscmp(pItem->GetName(),kOptionAlarmVoiceDefaultName)==0) {
				if (m_pm.FindControl(kOptionAlarmVoiceRecordName)) {
					m_pm.FindControl(kOptionAlarmVoiceRecordName)->SetFocus();
				}
				else {
					m_pm.FindControl(kBtAlarmVoiceRecordName)->SetFocus();
				}
			}
			else {
				m_pm.FindControl(kBtAlarmVoiceRecordName)->SetFocus();
			}
			break;

		case VK_BACK:
			/*
			if(voice Sets is change){
				if(idok==messagebox()){
					save();
				}
			}
			*/
			m_pm.FindControl(kSubMenuItemAlarmVoiceName)->SetFocus();
			break;
		}
		break;

		return false;
	}
	return true;
}

bool CMyMenuWnd::OnAlarmVoiceRecord(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CButtonUI* pItem = (CButtonUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_UP:
			if (m_pm.FindControl(kOptionAlarmVoiceRecordName)) {
				m_pm.FindControl(kOptionAlarmVoiceRecordName)->SetFocus();
			}
			else {
				m_pm.FindControl(kOptionAlarmVoiceDefaultName)->SetFocus();
			}
			break;

		//----------------------------------------------
		case VK_BACK:
			/*
			if(voice Sets is change){
			if(idok==messagebox()){
			save();
			}
			}
			*/
			m_pm.FindControl(kSubMenuItemAlarmVoiceName)->SetFocus();
			break;
		//----------------------------------------------
		case VK_RETURN:

			break;
		}
		break;

		return false;
	}
	return true;
}

bool CMyMenuWnd::OnAlarmLight(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	CSwitchExUI* pItem = (CSwitchExUI*)pMsg->pSender;
	switch (pMsg->Type) {
	case UIEVENT_KEYDOWN:
		switch (pMsg->wParam) {
		case VK_LEFT:
			if (pItem->GetValue()) {
				pItem->SetValue(false);
				pItem->Invalidate();
			}
			break;
		//----------------------------------------------
		case VK_RIGHT:
			if (!pItem->GetValue()) {
				pItem->SetValue(true);
				pItem->Invalidate();
			}
			break;
		//----------------------------------------------
		case VK_BACK:
			/*
			if(Sets is change){
				if(idok==messagebox()){
					save();
				}
			}
			*/
			m_pm.FindControl(kSubMenuItemAlarmLightName)->SetFocus();
			break;
		}
		break;

		return false;
	}
	return true;
}


bool CMyMenuWnd::OnRecords(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	return true;
}

bool CMyMenuWnd::OnHome(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	return true;
}


// SubMenuItem Add Or Delete
void CMyMenuWnd::AddAlarmSubMenu()
{

}

void CMyMenuWnd::AddVideoObtainSubMenu()
{

}

void CMyMenuWnd::AddPortConfigSubMenu()
{

}

void CMyMenuWnd::DeleteAlarmSubMenu()
{
}

void CMyMenuWnd::DeleteVideoObtainSubMenu()
{
}

void CMyMenuWnd::DeletePortConfigSubMenu()
{
}
 
bool CMyMenuWnd::AlarmVoideIsChange()
{
	CStdPtrArray* aOptionGroup = m_pm.GetOptionGroup(kAlarmVoiceGroupName);
	int sel = 0;
	for (; sel < aOptionGroup->GetSize(); sel++) {
		COptionUI* pControl = static_cast<COptionUI*>(aOptionGroup->GetAt(sel));
		if (pControl->IsSelected()) {
			break;
		}
	}
	return false;
}
