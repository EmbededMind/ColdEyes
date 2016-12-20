
// ColdEyesDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Layout.h"
#include "ColdEyes.h"
#include "ColdEyesDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CColdEyesDlg �Ի���



CColdEyesDlg::CColdEyesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COLDEYES_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void  CColdEyesDlg::GetAdaptablePos(CRect& r)
{
	int screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int height  = screenHeight;
	int width = 0;

	if (screenHeight / 3 > screenWidth / 4) {
		width  = screenWidth;
		height  = width *3/4;
	}
	else {
		width  = height *4/3;
	}

	r.left  = (screenWidth - width) / 2;
	r.right = (screenWidth + width) / 2;
	r.top   = (screenHeight - height) /2;
	r.bottom = (screenHeight + height) / 2;
}


void  CColdEyesDlg::UpdateLayout()
{
	CRect rClient;
	GetClientRect(&rClient);

	int titleHeight  = rClient.Height() * TITLE_HEIGHT;
	mTitleRect.left  = rClient.left;
	mTitleRect.top   = rClient.top;
	mTitleRect.right = rClient.right;
	mTitleRect.bottom= titleHeight;

	LayoutTitle(mTitleRect);

	mWall.SetWindowPos(NULL, rClient.left, rClient.top + titleHeight,
					rClient.Width(), rClient.Height() - titleHeight, SWP_NOZORDER);
}



void CColdEyesDlg::LayoutTitle(CRect& rTitle)
{
	int firstBkRight  = rTitle.Width() * rTitle.Width() * TITLE_SYSTIME_BK_WIDTH;

	mTitleTimeBkRect.left   = rTitle.left;
	mTitleTimeBkRect.top    = rTitle.top;
	mTitleTimeBkRect.right  = mTitleTimeBkRect.left + rTitle.Width() * TITLE_SYSTIME_BK_WIDTH;
	mTitleTimeBkRect.bottom = rTitle.bottom;

	mTitleAwBkRect.left     = mTitleTimeBkRect.right + 1;
	mTitleAwBkRect.top      = rTitle.top;
	mTitleAwBkRect.right    = mTitleAwBkRect.left + rTitle.Width() * TITLE_AW_BK_WIDTH;
	mTitleAwBkRect.bottom   = rTitle.bottom;

	mTitleHwBkRect.left     = mTitleAwBkRect.right + 1;
	mTitleHwBkRect.top      = rTitle.top;
	mTitleHwBkRect.right    = mTitleHwBkRect.left + rTitle.Width() * TITLE_HW_BK_WIDTH;
	mTitleHwBkRect.bottom   = rTitle.bottom;

	mTitleFont.DeleteObject();
	mTitleFont.CreatePointFont(rTitle.Height()*TITLE_FONT_HEIGHT*10,  TITLE_FONT);
}



void CColdEyesDlg::PaintTitle(CPaintDC& dc)
{
	CBrush  blackBrush;
	CBrush  whiteBrush;


    blackBrush.CreateSolidBrush(RGB(0, 0, 0));
	whiteBrush.CreateSolidBrush(RGB(58, 58, 58));
	

	CBrush* pOldBrush = dc.SelectObject(&blackBrush);

	CBrush  brush_black(RGB(0, 0, 0));
	CBrush  brush_white(RGB(58, 58, 58));
	CBrush* pBrush_old  = dc.SelectObject(&brush_black);

	CBrush   brush_left(RGB(0, 0, 0));

	
///****************** Draw title background *****************/
	int offset = mTitleRect.Height() * 0.288675;
	POINT bkPolygon[4];
//
	 //Draw system time background
	bkPolygon[0].x  = mTitleTimeBkRect.left;
	bkPolygon[0].y  = mTitleTimeBkRect.top;
	bkPolygon[1].x  = mTitleTimeBkRect.right + offset;
	bkPolygon[1].y  = mTitleTimeBkRect.top;
	bkPolygon[2].x  = mTitleTimeBkRect.right - offset;
	bkPolygon[2].y  = mTitleTimeBkRect.bottom;
	bkPolygon[3].x  = mTitleTimeBkRect.left;
	bkPolygon[3].y  = mTitleTimeBkRect.bottom;
	
	dc.Polygon(bkPolygon, 4);
	
//
//
	//Draw home watch background
	bkPolygon[0].x = mTitleHwBkRect.left + offset;
	bkPolygon[0].y = mTitleHwBkRect.top;
	bkPolygon[1].x = mTitleHwBkRect.right;
	bkPolygon[1].y = mTitleHwBkRect.top;
	bkPolygon[2].x = mTitleHwBkRect.right ;
	bkPolygon[2].y = mTitleHwBkRect.bottom;
	bkPolygon[3].x = mTitleHwBkRect.left - offset;
	bkPolygon[3].y = mTitleHwBkRect.bottom;

	dc.Polygon(bkPolygon, 4);	



	// Draw auto watch background	
	bkPolygon[0].x = mTitleAwBkRect.left + offset;
	bkPolygon[0].y = mTitleAwBkRect.top;
	bkPolygon[1].x = mTitleAwBkRect.right + offset;
	bkPolygon[1].y = mTitleAwBkRect.top;
	bkPolygon[2].x = mTitleAwBkRect.right - offset;
	bkPolygon[2].y = mTitleAwBkRect.bottom;
	bkPolygon[3].x = mTitleAwBkRect.left - offset;
	bkPolygon[3].y = mTitleAwBkRect.bottom;

	//dc.SelectObject(&whiteBrush);
	dc.SelectObject(&brush_white);
	dc.Polygon(bkPolygon, 4);
	

	//dc.SelectObject(pOldBrush);
	dc.SelectObject(pBrush_old);
}



void CColdEyesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CColdEyesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_MESSAGE(USER_MSG_FIND_DEV, &CColdEyesDlg::OnUserMsgFindDev)
END_MESSAGE_MAP()


// CColdEyesDlg ��Ϣ�������

BOOL CColdEyesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	mWall.Create(IDD_WALL, this);
	mWall.ShowWindow(SW_SHOW);

	//pWallWindow  = new CWallWindow();
	//pWallWindow->Create(NULL, NULL, UI_WNDSTYLE_CHILD | UI_WNDSTYLE_DIALOG, 0);
	//pWallWindow->ShowWindow(SW_SHOW);


	CRect r;
	GetAdaptablePos(r);
	SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), 0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CColdEyesDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CColdEyesDlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		PaintTitle(dc);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CColdEyesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CColdEyesDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (IsWindow(mWall)) {
		UpdateLayout();
	}		
}


afx_msg LRESULT CColdEyesDlg::OnUserMsgFindDev(WPARAM wParam, LPARAM lParam)
{
	if (wParam) {
		Print("OnFindDevice true");
	}
	else {
		Print("OnFindDevice false");
	}
	return 0;
}
