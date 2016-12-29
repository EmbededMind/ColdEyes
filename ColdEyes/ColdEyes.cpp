
// ColdEyes.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ColdEyes.h"
#include "ColdEyesDlg.h"

#include "NetSdk\netsdk.h"

#include "DuiLib\UIlib.h"

#include "MainWindow.h"


//#include "Com\Router.h"
#include "Com\SerialPort.h"
#include "Device\DeviceDetecter.h"


#include "Database\DBHelper.h"

#include "Config\SystemConfig.h"

#include "Device\Port.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifdef USE_PRINT
void InitConsoleWindow()
{
	::AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
}
#endif


void NetSdkInit()
{

}

// CColdEyesApp

BEGIN_MESSAGE_MAP(CColdEyesApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CColdEyesApp 构造

CColdEyesApp::CColdEyesApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CColdEyesApp 对象

CColdEyesApp theApp;


// CColdEyesApp 初始化

BOOL CColdEyesApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

#ifdef USE_PRINT
	InitConsoleWindow();
#endif

	CDBHelper& DBHelper  = CDBHelper::GetInstance();
	if(DBHelper.OpenDatabase("cold_eyes.db")){
		CPort Port;	
		Port.mPos  = 2;
		Port.SetId(1);
		Port.CommitUpdate();
	}
	
	CSerialPort* pSerialPort  = CSerialPort::GetInstance(COM_103);

	mRouter.AttachSender(pSerialPort);
	
	if ( !pSerialPort->InitPort(&mRouter, COM_103, 9600, 'N', 8, 1, EV_RXCHAR, 512)) {
		Print("Exception : 103 port init failed!");
	}
	else {
		pSerialPort->StartMonitoring();
	}

	CDeviceDetecter* pDD = CDeviceDetecter::GetInstance();
	mRouter.RegisterHandler(pDD, 0x05);
	//pDD->StartDetect();



	using namespace DuiLib;

	CPaintManagerUI::SetInstance(AfxGetInstanceHandle());
	CPaintManagerUI::SetResourcePath(_T(UI_RESOURCE_PATH));

	
	REGIST_DUICONTROL(CMenuItemUI);
	REGIST_DUICONTROL(CSubMenuItemUI);
	REGIST_DUICONTROL(CKeyBoardUI);
	REGIST_DUICONTROL(CSliderExUI);
	REGIST_DUICONTROL(CLabelExUI);
	REGIST_DUICONTROL(CTimeSpanPickerUI);
	REGIST_DUICONTROL(CSwitchExUI);
	REGIST_DUICONTROL(CEditExUI);
	REGIST_DUICONTROL(COptionExUI);
	REGIST_DUICONTROL(CCameraNameElementUI);

	CColdEyesDlg dlg;
	m_pMainWnd = &dlg;
	pSerialPort->AttachWindow(m_pMainWnd);
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

