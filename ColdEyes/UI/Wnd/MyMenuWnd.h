#pragma once

#include "DuiLib/UIlib.h"

#include <list>
#include "UI\Control\EditExUI.h"
#include "UI\Control\SubMenuItemUI.h"
#include "UI\Control\KeyBoardUI.h"
#include "UI\Control\SliderExUI.h"
#include "UI\Control\LabelExUI.h"
#include "UI\Control\TimeSpanPickerUI.h"
#include "UI\Control\SwitchExUI.h"
#include "UI\Control\OptionExUI.h"

//MenuItmLayout
const TCHAR* const KLayoutParentMenuName = _T("layout_parent_menu");
const TCHAR* const kLayoutChildrenMenuName = _T("layout_children_menu");

//	Parent MenuItem
const TCHAR* const kMenuItemAlarmVideoName = _T("parent_menu_alarm_video");
const TCHAR* const kMenuItemHostSetName = _T("parent_menu_host_set");
const TCHAR* const kMenuItemAutoWatchName = _T("parent_menu_auto_watch");
const TCHAR* const kMenuItemVideoObtainName = _T("parent_menu_video_obtain");
const TCHAR* const KMenuItemHomeWatchName = _T("parent_menu_home_watch");

//SubMenuItemLayout
const TCHAR* const kLayoutSubAlarmVideoName = _T("layout_submenu_alarm_video");
const TCHAR* const kLayoutSubHostSetName = _T("layout_submenu_host_set");
const TCHAR* const kLayoutSubAutoWatchName = _T("layout_submenu_auto_watch");
const TCHAR* const kLayoutSubVideoObtainName = _T("layout_submenu_video_obtain");

//SubMenu
const TCHAR* const kSubMenuItemHostName = _T("host_name");
const TCHAR* const kSubMenuItemSysSetName = _T("sys_set");

const TCHAR* const kSubMenuItemAwTimeName = _T("aw_time");
const TCHAR* const kSubMenuItemAlarmVoiceName = _T("alarm_voice");
const TCHAR* const kSubMenuItemAlarmLightName = _T("alarm_light");
const TCHAR* const kSubMenuItemAwOnOffRecordName = _T("aw_on_off_record");


// BodyLayout
const TCHAR* const kBodyLayoutAlarmVideo = _T("body_alarm_video");
const TCHAR* const kBodyLayoutHostSetName = _T("body_host_set");
const TCHAR* const kBodyLayoutAwTime = _T("body_auto_watch");
const TCHAR* const kBodyLayoutVideoObtain = _T("body_video_obtain");


//host name
const TCHAR* const kEditCtlHostNameName = _T("edit_host_name");
const TCHAR* const kKeyboardName = _T("keyboard");
const TCHAR* const kLayoutPromptName = _T("layout_prompt");

//auot time
const TCHAR* const kTimeSpanPickerAwName = _T("time_span_picker_aw");

//sysset
const TCHAR* const kSysBrightName = _T("sysset_brightness");
const TCHAR* const kSysVolumeName = _T("sysset_volume");
const TCHAR* const kSysVersionName = _T("sysset_version");
const TCHAR* const kSysFactoryName = _T("sysset_factory");
const TCHAR* const kSysHostModelName = _T("sysset_host_model");
const TCHAR* const kSysSerialNumberName = _T("sysset_host_series_number");

//alarm voice
const TCHAR* const kSwitchAlarmVoiceName = _T("switch_alarm_voice");
const TCHAR* const kOptionAlarmVoiceDefaultName = _T("voice_default");
const TCHAR* const kOptionAlarmVoiceRecordName = _T("voice_record");
const TCHAR* const kBtAlarmVoiceRecordName = _T("record_btn");
const TCHAR* const kAlarmVoiceGroupName = _T("grop_alarm_voice");

//alarm light
const TCHAR* const kAlarmLightName = _T("switch_alarm_light");

//==============BkColor=====================
#define LAYOUT_MENUITEM_FOCUSED		0xFFFFFFFF
#define	LAYOUT_MENUITEM_NOFOCUS		0xFFE6E6EF

#define LAYOUT_SUB_FOCUSED			0xFFFFFFFF
#define LAYOUT_SUB_NOFOCUS			0xFFE6E6EF
#define LAYOUT_SUB_SEL_NOFOCUS		0xFFEFEFF4

#define LAYOUT_BODY_NOFOUCS			0xFFEFEFF4
#define LAYOUT_BODY_FOCUSED			0xFFFFFFFF

#define ITEM_FOCUS					0xFF4198FE
#define MENUITEM_SEL_NOFOCUS		0xFF47688F
#define SUBMENUITEM_SEL_NOFOCUS		0xFF4178B7


using namespace DuiLib;


class CMyMenuWnd
	: public WindowImplBase
{
public:
	CMyMenuWnd();
	~CMyMenuWnd();

	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	void Notify(TNotifyUI& msg);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void InitWindow();
	void UpdataBkColor(int focusLevel,DWORD Color1,DWORD Color2);


	void MakeItemsDelegate();	//控件委托函数初始化
	void MenuItemMakeDelegate(const TCHAR* const Name);
	void SubMenuMakeDelegate(const TCHAR* const Name);	//二级子控件委托设置

	/************ Delegate Functions****************/
	bool OnMenuItem(void* param);
	bool OnSubMenuItem(void*param);
	bool OnHostName(void* param);

	bool OnAlarmFileList(void* param);
	bool OnNormalFileList(void* param);

	bool OnCameraName(void* param);
	bool OnCameraVolume(void* param);
	bool OnCameraSwitch(void* param);
	bool OnCameraStore(void* param);
	bool OnCameraAutoWatch(void* param);

	bool OnSysBrightness(void* param);
	bool OnSysVolume(void* param);
	bool OnSysVersion(void* param);
	bool OnFactorySet(void* param);
	bool OnSysHostModel(void* parma);
	bool OnSysSerialNumber(void* param);

	bool OnAwTime(void* param);
	bool OnAlarmVoiceSwitch(void* param);
	bool OnAlarmVoiceOption(void* param);
	bool OnAlarmVoiceRecord(void* param);
	bool OnAlarmLight(void* param);
	bool OnRecords(void* param);
	bool OnHome(void* param);

	//Add SubMenuItem
	void  AddAlarmSubMenu();		//报警视频
	void  AddVideoObtainSubMenu();	//视频调取
	void  AddPortConfigSubMenu();	//摄像头设置

	//Delete SubMenuItem
	void  DeleteAlarmSubMenu();
	void  DeleteVideoObtainSubMenu();
	void  DeletePortConfigSubMenu();

	//Sets is change
	bool AlarmVoideIsChange();


private:
	int mDPI;

	CControlUI* pKillFocsedItem ;
	CDuiString FocusedItemClassName;
};


