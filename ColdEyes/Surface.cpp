#include "stdafx.h"
#include "Surface.h"


int __stdcall cbRealData(long handle, const PACKET_INFO_EX* pFrame, UINT userData)
{
	CSurface* pSurface  = (CSurface*)userData;

	if (pSurface->IsRealPlaying()) {
		H264_PLAY_InputData(pSurface->GetPlayPort(), (unsigned char*)pFrame->pPacketBuffer, pFrame->dwPacketSize);
	}
	return 1;
}



void CALLBACK cbOsdDraw(long port, HDC hDC, long userData)
{

}



IMPLEMENT_DYNAMIC(CSurface, CWnd)

CSurface::CSurface()
{
	RegisterWindowClass();
	mClientInfo.nChannel  = 0;
	mClientInfo.nMode     = 0;
	mClientInfo.nStream   = 1;
}



CSurface::~CSurface()
{

}




void CSurface::BindPort(CPort* pPort)
{
	this->mPort  = pPort;
}



bool CSurface::IsRealPlaying()
{
	return mIsRealPlaying;
}



long CSurface::GetPlayPort()
{
	return mPlayPort;
}


/** 打开实时数据通道
 *
 */
bool CSurface::ConnectRealPlay()
{
	ASSERT(mPort && mPort->GetBindedCamera());

	mRealPlayHandle  = H264_DVR_RealPlay(mPort->GetBindedCamera()->GetLoginId(), &mClientInfo);

	if (mRealPlayHandle != 0) {
		if (H264_DVR_SetRealDataCallBack_V2(mRealPlayHandle, cbRealData, (long)this)) {
			return true;
		}
		else {
			Print("Set cbRealPlay failed:%d", H264_DVR_GetLastError());
		}
	}

	return false;
}


/** 关闭实时数据通道
 *
 */
bool CSurface::DisconnectRealPlay()
{
	if (mRealPlayHandle != 0) {
		H264_DVR_DelRealDataCallBack_V2(mRealPlayHandle, cbRealData, (long)this);

		if ( H264_DVR_StopRealPlay(mRealPlayHandle)) {			
			return true;
		}
		else {
			Print("Stop real play failed:%d", H264_DVR_GetLastError());
		}
	}
	
	return false;
}



void CSurface::SetPos()
{
	SetWindowPos(NULL, mSplitPos.left, mSplitPos.top, mSplitPos.Width(), mSplitPos.Height(), 0);
}



void CSurface::SetPos(CRect& r)
{
	mSplitPos  = r;

	if (!mIsLargeMode) {
		SetWindowPos(NULL, mSplitPos.left, mSplitPos.top, mSplitPos.Width(), mSplitPos.Height(), 0);
	}
}



void CSurface::OnCameraLogin()
{
	if (ConnectRealPlay()) {
		StartRealPlay();
	}
}



BOOL  CSurface::RegisterWindowClass(HINSTANCE hInstance)
{
	LPCWSTR className  = _T("CSurface");

	WNDCLASS windowclass;

	if (!hInstance) {
		hInstance  = AfxGetInstanceHandle();
	}

	if (!(::GetClassInfo(hInstance, className, &windowclass))) {
		windowclass.style = CS_DBLCLKS;
		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
		windowclass.hInstance = hInstance;
		windowclass.hIcon = NULL;
		windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
		windowclass.lpszMenuName = NULL;
		windowclass.lpszClassName = className;

		if (!AfxRegisterClass(&windowclass)) {
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}



bool CSurface::StartRealPlay()
{
	BYTE fileHeadBuf;

	if (!H264_PLAY_GetPort(&mPlayPort)) {
		return false;
	}

	if (H264_PLAY_OpenStream(mPlayPort, &fileHeadBuf, 1, SOURCE_BUF_MIN * 100)) {
		H264_PLAY_DeleteOsdTex(mPlayPort, mOsdTextIndex);
		mOsdTextIndex  = H264_PLAY_SetOsdTex(mPlayPort, &mOsdText);

		H264_PLAY_RigisterDrawFun(mPlayPort, cbOsdDraw, (DWORD)this);
		
		if (!H264_PLAY_SetStreamOpenMode(mPlayPort, STREAME_REALTIME)) {
			Print("Set REALTIME stream mode failed:%d", H264_PLAY_GetLastError(mPlayPort));
			return false;
		}

	    mClientInfo.hWnd  = this->m_hWnd;
		if (! H264_PLAY_Play(mPlayPort, (HWND)mClientInfo.hWnd)) {
			Print("Play failed:%d", H264_PLAY_GetLastError(mPlayPort));
			return false;
		}

		mIsRealPlaying  = true;
	}
	else {		
		return false;
	}
}



bool CSurface::StopRealPlay()
{
	mIsRealPlaying  = false;
	if (H264_PLAY_Stop(mPlayPort)) {
		return true;
	}
	else {
		Print("Stop real play failed:%d", H264_PLAY_GetLastError(mPlayPort));
		return false;
	}	
}