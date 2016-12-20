#include "stdafx.h"
#include "Surface.h"


IMPLEMENT_DYNAMIC(CSurface, CWnd)

CSurface::CSurface()
{
	RegisterWindowClass();
}



CSurface::~CSurface()
{

}




void CSurface::BindPort(CPort* pPort)
{
	this->mPort  = pPort;
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