#include "stdafx.h"
#include "SurfaceFrame.h"

CSurfaceFrame::CSurfaceFrame()
{

}



CSurfaceFrame::CSurfaceFrame(CWnd* pPaintWnd)
{
	this->pPaintWnd  = pPaintWnd;
}



CSurfaceFrame::~CSurfaceFrame()
{

}



void CSurfaceFrame::PaintBorder()
{
	if (pPaintWnd != NULL) {
		CDC* pDC  = pPaintWnd->GetDC();

		pDC->Rectangle(this);

		
	}
}



void CSurfaceFrame::SetPaintWindow(CWnd* pPaintWnd)
{
	this->pPaintWnd  = pPaintWnd;
}

