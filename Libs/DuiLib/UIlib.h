#ifdef UILIB_STATIC
#define UILIB_API 
#else
#if defined(UILIB_EXPORTS)
#	if defined(_MSC_VER)
#		define UILIB_API __declspec(dllexport)
#	else
#		define UILIB_API 
#	endif
#else
#	if defined(_MSC_VER)
#		define UILIB_API __declspec(dllimport)
#	else
#		define UILIB_API 
#	endif
#endif
#endif
#define UILIB_COMDAT __declspec(selectany)

#pragma warning(disable:4251)

#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <stddef.h>
#include <richedit.h>
#include <tchar.h>
#include <assert.h>
#include <crtdbg.h>
#include <malloc.h>
#include <comdef.h>
#include <gdiplus.h>

#include "DuiLib/Utils/Utils.h"
#include "DuiLib/Utils/VersionHelpers.h"
#include "DuiLib/Core/UIMarkup.h"
#include "DuiLib/Utils/observer_impl_base.h"
#include "DuiLib/Utils/UIShadow.h"
#include "DuiLib/Utils/UIDelegate.h"
#include "DuiLib/Utils/DragDropImpl.h"
#include "DuiLib/Utils/TrayIcon.h"
#include "DuiLib/Utils/DPI.h"

#include "DuiLib/Core/UIDefine.h"
#include "DuiLib/Core/UIResourceManager.h"
#include "DuiLib/Core/UIManager.h"
#include "DuiLib/Core/UIBase.h"
#include "DuiLib/Core/ControlFactory.h"
#include "DuiLib/Core/UIControl.h"
#include "DuiLib/Core/UIContainer.h"

#include "DuiLib/Core/UIDlgBuilder.h"
#include "DuiLib/Core/UIRender.h"
#include "DuiLib/Utils/WinImplBase.h"

#include "DuiLib/Layout/UIVerticalLayout.h"
#include "DuiLib/Layout/UIHorizontalLayout.h"
#include "DuiLib/Layout/UITileLayout.h"
#include "DuiLib/Layout/UITabLayout.h"
#include "DuiLib/Layout/UIChildLayout.h"

#include "DuiLib/Control/UIList.h"
#include "DuiLib/Control/UICombo.h"
#include "DuiLib/Control/UIScrollBar.h"
#include "DuiLib/Control/UITreeView.h"

#include "DuiLib/Control/UILabel.h"
#include "DuiLib/Control/UIText.h"
#include "DuiLib/Control/UIEdit.h"
#include "DuiLib/Control/UIGifAnim.h"
#include "DuiLib/Control/UIGifAnimEx.h"

#include "DuiLib/Control/UIAnimation.h"
#include "DuiLib/Layout/UIAnimationTabLayout.h"
#include "DuiLib/Control/UIButton.h"
#include "DuiLib/Control/UIOption.h"

#include "DuiLib/Control/UIProgress.h"
#include "DuiLib/Control/UISlider.h"

#include "DuiLib/Control/UIComboBox.h"
#include "DuiLib/Control/UIRichEdit.h"
#include "DuiLib/Control/UIDateTime.h"
#include "DuiLib/Control/UIIPAddress.h"

#include "DuiLib/Control/UIActiveX.h"
#include "DuiLib/Control/UIWebBrowser.h"
#include "DuiLib/Control/UIFlash.h"

#include "DuiLib/Control/UIMenu.h"
#include "DuiLib/Control/UIGroupBox.h"
#include "DuiLib/Control/UIRollText.h"
#include "DuiLib/Control/UIColorPalette.h"
#include "DuiLib/Control/UIListEx.h"
#include "DuiLib/Control/UIHotKey.h"
#include "DuiLib/Control/UIFadeButton.h"



#pragma comment( lib, "comctl32.lib" )
#pragma comment( lib, "GdiPlus.lib" )
#pragma comment( lib, "Imm32.lib" )