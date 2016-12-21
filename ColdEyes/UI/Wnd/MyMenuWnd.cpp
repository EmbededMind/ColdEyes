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

void CMyMenuWnd::SubMenuMakeDelegate(const TCHAR* const Name)
{
	static_cast<CSubMenuItemUI*>(m_pm.FindControl(Name))->OnEvent += MakeDelegate(this, &CMyMenuWnd::OnSubMenuItem);
}


/*************** Delegate Functions*********************/
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
			break;
		}
		break;
	//----------------------------------------------
	case UIEVENT_SETFOCUS:
		Item->SetStatus(false);
		if (m_pm.FindControl(kKeyboardName)->IsVisible()) {
			m_pm.FindControl(kKeyboardName)->SetVisible(false);
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
	return false;
}

bool CMyMenuWnd::OnHome(void * param)
{
	TEventUI* pMsg = (TEventUI*)param;
	return false;
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
