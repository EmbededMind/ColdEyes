#pragma once

#include "DuiLib\UIlib.h"
#include "VPlayer.h"
#include "AlphaMarkWnd.h"
#include "NetSdk\H264Play.h"
#include "MyMenuWnd.h"

#include <list>


//class CPlayerWallWnd;
class CAlphaMarkWnd;
class CMyMenuWnd;

using namespace std;

using namespace DuiLib;

enum PlayStatus
{
	stop = 0,
	playing,
	pause,
	slow_fast
};

class CPlayerWallWnd :
	public WindowImplBase{

public:
	CPlayerWallWnd();
	CPlayerWallWnd(CDuiString);
	~CPlayerWallWnd();
	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void InitWindow();

private:
	CDuiString mSkinFileName;

	CVPlayer* pVPlayerWnd;
	CAlphaMarkWnd* pMarkWnd;

	// pItem 
	CButtonUI* pSlow;
	CButtonUI* pPlay;
	CButtonUI* pFast;
	CLabelUI* pBeginTime;
	CLabelUI* pEndTime;
	CSliderUI* pSlider;
};