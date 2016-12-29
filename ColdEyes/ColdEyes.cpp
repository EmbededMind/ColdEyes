
// ColdEyes.cpp : ����Ӧ�ó��������Ϊ��
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


// CColdEyesApp ����

CColdEyesApp::CColdEyesApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CColdEyesApp ����

CColdEyesApp theApp;


// CColdEyesApp ��ʼ��

BOOL CColdEyesApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

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
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

