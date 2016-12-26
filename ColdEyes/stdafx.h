
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��




/// Load sqlite library
#pragma comment(lib, "sqlite3.lib")

/// Load Dui library
#ifndef _DEBUG
#pragma comment(lib, "Duilib.lib")
#else
#pragma comment(lib, "Duilib_d.lib")
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


#define USER_MSG_SYS_VOLUME				 (WM_USER + 210) //ϵͳ����
#define USER_MSG_SYS_LIGHT				 (WM_USER + 211)	// ϵͳ����

 /*****************************************
 *            Direction define            *
 ******************************************/
#define UI_RESOURCE_PATH           "..\\Resource"


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


