#pragma once

#include "Surface.h"

// WallDlg 对话框

class CWallDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWallDlg)

public:
	CWallDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWallDlg();


public:
	CSurface* mSurfaces[PORT_MAX_NUM];
	int       mSurfaceNumber;
	int       mCols;
	int       mRows;


	void DesignSurfaceLayout();
	void ExecuteSurfaceLayout();
	CSurface* Ingest(CPort* pPort);
	void TestIngestOne();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnUserMsgFindDev(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUserMsgLogin(WPARAM wParam, LPARAM lParam);
};
