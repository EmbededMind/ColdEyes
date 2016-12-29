
// ColdEyesDlg.h : ͷ�ļ�
//

#pragma once
#include "MyMenuWnd.h"

class CMyMenuWnd;
#include "WallDlg.h"

//#include "UI\Wnd\WallWindow.h"


#define GetWallWnd      (&(((CColdEyesDlg*)AfxGetMainWnd())->mWall))

// CColdEyesDlg �Ի���
class CColdEyesDlg : public CDialogEx
{
// ����
public:
	CColdEyesDlg(CWnd* pParent = NULL);	// ��׼���캯��


public:
	CMyMenuWnd* mMenu;


	CWallDlg    mWall;

	
private:
	CRect       mTitleRect;

	CRect       mTitleTimeBkRect;
	CRect       mTitleAwBkRect;
	CRect       mTitleHwBkRect;
	CRect       mTitleFlashBkRect;

	CFont       mTitleFont;


	void        GetAdaptablePos(CRect& r);
	void        UpdateLayout();
	void        LayoutTitle(CRect& r);


	void        PaintTitle(CPaintDC& dc);

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLDEYES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
	afx_msg LRESULT OnUserMsgFindDev(WPARAM wParam, LPARAM lParam);
};
