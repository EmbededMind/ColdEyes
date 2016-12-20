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

//	Parent MenuItem
const TCHAR* const kMenuItemAlarmVideoName = _T("parent_menu_alarm_video");
const TCHAR* const kMenuItemHostSetName = _T("parent_menu_host_set");
const TCHAR* const kMenuItemAutoWatchName = _T("parent_menu_auto_watch");
const TCHAR* const kMenuItemVideoObtainName = _T("parent_menu_video_obtain");
const TCHAR* const KMenuItemHomeWatchName = _T("parent_menu_home_watch");

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
	void InitMenuItem();
	void LayoutInit();
	void AddLayout(LPCTSTR xmlName,CContainerUI* ParentLayout);
	void AddAtLayout(LPCTSTR xmlName, CContainerUI* ParentLayout,UINT8 inx);
	void SetSubMenuParent(LPCTSTR sSubMenuName, LPCTSTR sParentName);

	void MakeItemsDelegate();	//控件委托函数初始化
	void SubMenuMakeDelegate(const TCHAR* const Name);	//二级子控件委托

	// item Delegate
	bool OnSubMenuItem(void*param);

	//Add SubMenuItem
	void  AddAlarmMenuItem();		//报警视频
	void  AddVideoObtainMenuItem();	//视频调取
	void  AddPortConfigMenuItem();	//摄像头设置

	//Delete SubMenuItem
	void  DeleteAlarmMenuItem();
	void  DeleteVideoObtainMenuItem();
	void  DeletePortConfigMenuItem();

private:
	int mDPI;
};


