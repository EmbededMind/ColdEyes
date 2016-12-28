#pragma once
#include "stdafx.h"



class CSurfaceFrame : CRect
{
	friend class CSurface;
public :
	CSurfaceFrame();
	CSurfaceFrame(CWnd* pPaintWnd);
	~CSurfaceFrame();

	void SetPaintWindow(CWnd* pPaintWnd);


protected:
	CWnd* pPaintWnd;


	void  PaintBorder();
};
