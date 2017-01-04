
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持





#ifndef _DEBUG
#pragma comment(lib, "Duilib.lib")
#pragma comment(lib, "sqlite3.lib")
#else
#pragma comment(lib, "Duilib_d.lib")
#pragma comment(lib, "sqlite3_d.lib")
#endif


/// Load NetSdk library
#pragma comment(lib, "H264Play.lib")
#pragma comment(lib, "NetSdk.lib")



//  Macro about device
#define PORT_MAX_NUM         6



//  Macro about timer
#define TICK_ELAPSE_SEC      5
#define TICK_ACK_TIMEOUT_CNT 3
#define ACK_TIMEOUT_MILLMS   2000

//  Macro about com
#define COM_KB               1
#define COM_103              4


#define USE_PRINT

#ifdef USE_PRINT
#define Print(format, ...)   printf(format"\n", __VA_ARGS__)
#elif
#define Print(format, ...)
#endif


/**********************************************************************
 *                         User msg define                            *
 **********************************************************************/
#define USER_MSG_SCAN_DEV                (WM_USER + 100)

#define USER_MSG_FIND_DEV                (WM_USER + 110)
#define USER_MSG_LOGIN                   (WM_USER + 111)
#define USER_MSG_LOGOUT                  (WM_USER + 112)


#define USER_MSG_SYS_VOLUME				 (WM_USER + 210) //系统音量
#define USER_MSG_SYS_LIGHT				 (WM_USER + 211)	// 系统亮度

#define USER_MSG_COPY_PRO				 (WM_USER + 220)
#define USER_MSG_COPY_END                (WM_USER + 221)
#define USER_MSG_COPY_NOSPACE            (WM_USER + 222)
#define USER_MSG_COPY_DISKOUT            (WM_USER + 223)

 /*****************************************
 *            Direction define            *
 ******************************************/
#define UI_RESOURCE_PATH           "..\\Resource"



 //系统音量设置
#define HOST_VOICE_LEVEL_0          0
#define HOST_VOICE_LEVEL_1          1
#define HOST_VOICE_LEVEL_2          2
#define HOST_VOICE_LEVEL_3          3
#define HOST_VOICE_LEVEL_4          4
#define HOST_VOICE_LEVEL_5          5
#define HOST_VOICE_LEVEL_6          6
#define HOST_VOICE_LEVEL_7          7
#define HOST_VOICE_LEVEL_8          8
#define HOST_VOICE_LEVEL_9          9
#define HOST_VOICE_LEVEL_10         10
#define HOST_VOICE_MUTE             11
#define HOST_VOICE_NOMUTE           12
#define HOST_VOICE_LEVEL_UP         13
#define HOST_VOICE_LEVEL_DOWN       14

// Function declartion
void IPNumberToStr(UINT8* pData, char* ip);
void MacNumberToStr(UINT8* pNumber, char* pMac);


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


