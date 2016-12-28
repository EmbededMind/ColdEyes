// WallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Layout.h"
#include "ColdEyes.h"
#include "WallDlg.h"
#include "afxdialogex.h"


#include "NetSdk\netsdk.h"

#include "Device\Port.h"
#include "Device\DeviceDetecter.h"

/** SDK报警消息回调
 *
 */
bool __stdcall cbAlarmMessage(long loginId, char* pBuf, unsigned long bufLen, long userData)
{
	Print("Alarm cb");
	return 0;
}




/** 摄像头掉线回调
 *
 */
void __stdcall cbDisconnect(LONG loginId, char* ip, LONG port, DWORD userData)
{

}





// CWallDlg 对话框

IMPLEMENT_DYNAMIC(CWallDlg, CDialogEx)

CWallDlg::CWallDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WALL, pParent)
{

}

CWallDlg::~CWallDlg()
{
}



void CWallDlg::DesignSurfaceLayout()
{
	int i  = 0;
	
	if (mSurfaceNumber > 0) {
		int qVal  = 0;

		while (i <= mSurfaceNumber) {
			qVal  = i*i;
			if (qVal >= mSurfaceNumber) {
				mCols  = i;
				break;
			}
			i++;
		}

		mRows = mSurfaceNumber / mCols + ((mSurfaceNumber % mCols) > 0 ? 1 : 0);
		Print("Rows:%d, Cols:%d", mRows, mCols);
	}
}



void CWallDlg::ExecuteSurfaceLayout()
{
	CRect rClient;
	GetClientRect(&rClient);
	
	float hMargin  = rClient.Width() * HOR_MARGIN_SCALE;
	float vMargin  = rClient.Height() * VTC_MARGIN_SCALE;
	float grap     = rClient.Height() * GRAP_SCALE;

	float hLimit  = (rClient.Width() - 2*(hMargin + grap*mCols)) /4 / mCols;
	float vLimit  = (rClient.Height() - 2*(vMargin + grap*mRows)) /3 /mRows;
	float limit   = hLimit > vLimit ? vLimit : hLimit;

	int yOrg  = (rClient.Height() - (3*limit + 2*grap) *mRows) / 2;
	int xOrg  = (rClient.Width() - (4*limit + 2*grap) *mCols) / 2;


	int width  = 4 * limit;
	int height = 3 * limit;


	CRect r;
	int cnt  = 0;
	for (int i = 0; cnt < mSurfaceNumber; i++) {
		if (mSurfaces[i] != NULL) {
			int xPos  = xOrg + (cnt % mCols) * (width + grap *2);
			int yPos  = yOrg + (cnt / mCols) * (height + grap *2);

			r.left  = xPos + grap;
			r.right = r.left + width;
			r.top   = yPos + grap;
			r.bottom= r.top + height;


			mSurfaces[i]->SetPos(r);
			cnt++;
		}
	}
}



CSurface* CWallDlg::Ingest(CPort* pPort)
{
	ASSERT(pPort->GetId() > 0);

	int inx  = pPort->GetId() -1;

	if (mSurfaces[inx] == NULL) {
		mSurfaces[inx]  = new CSurface();
		mSurfaces[inx]->Create(NULL, _T("Surface"), WS_CHILD|WS_VISIBLE|WS_THICKFRAME, CRect(0, 0, 0, 0), this, pPort->GetId());
		mSurfaces[inx]->BindPort(pPort);
		
		mSurfaceNumber++;		
		return mSurfaces[inx];
	}
	return NULL;
}




void CWallDlg::TestIngestOne()
{
	static int id  = 0;
	if (id < 6) {
		id++;

		CPort* pNewPort = new CPort();
		pNewPort->SetId(id);
		Ingest(pNewPort);
		delete pNewPort;

		DesignSurfaceLayout();
		ExecuteSurfaceLayout();
	}
}




void CWallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWallDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_FIND_DEV, &CWallDlg::OnUserMsgFindDev)
	ON_MESSAGE(USER_MSG_LOGIN, &CWallDlg::OnUserMsgLogin)
END_MESSAGE_MAP()


// CWallDlg 消息处理程序


BOOL CWallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	H264_DVR_Init(cbDisconnect,  (DWORD)this);
	H264_DVR_SetDVRMessCallBack(cbAlarmMessage, (DWORD)this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


/** 扫描到Port对应的设备的消息
 *
 */
afx_msg LRESULT CWallDlg::OnUserMsgFindDev(WPARAM wParam, LPARAM lParam)
{
	CPort* pPort  = (CPort*)lParam;

	if (pPort && wParam) {
		CSurface * pSurface  = Ingest(pPort);
		if (pSurface) {
			DesignSurfaceLayout();
			ExecuteSurfaceLayout();
			UINT pid  = CDeviceDetecter::GetInstance()->GetLoginThreadPid();
			Print("Post login msg port is :%d", pPort->GetId());
			PostThreadMessage(pid, USER_MSG_LOGIN, (WPARAM)m_hWnd, (LPARAM)pPort);
		}
	}

	return 0;
}


BOOL CWallDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
			case VK_UP:
				TestIngestOne();
				return true;
			break;
			//-----------------------------
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


afx_msg LRESULT CWallDlg::OnUserMsgLogin(WPARAM wParam, LPARAM lParam)
{
	CPort* pPort  = (CPort*)lParam;
	
	if (wParam) {		
		Print("Login ok");
		CSurface* pSurface  = mSurfaces[pPort->GetId()-1];
		if (pSurface) {
			pSurface->OnCameraLogin();
		}
		else {
			Print("Exception:Login but have no surface");
		}
	}
	else {
		Print("Login failed");
	}
	return 0;
}
