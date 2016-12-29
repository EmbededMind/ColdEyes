#pragma once

#include "DuiLib\UIlib.h"
#include "VPlayer.h"
#include "AlphaMarkWnd.h"
#include "NetSdk\H264Play.h"
#include "MyMenuWnd.h"
#include "ColdEyes.h"
#include "ColdEyesDlg.h"

#include <list>


#define BACKSPACE_1	41 
#define BACKSPACE_2	20
#define BACKSPACE_3	10
#define BACKSPACE_4 5


class CColdEyesDlg;
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

	virtual LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	void InitWindow();
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
	void InitPlayOptionImage();
	void PreparePlay();
	void OpenFile();

	BOOL StopPlay();

	void OnBack();
	void OnFast();
	void OnPlay();

private:
	CDuiString mSkinFileName;

	CVPlayer* pVPlayerWnd;
	CAlphaMarkWnd* pMarkWnd;

	long m_Port;

	// pItem 
	CButtonUI* pSlow;
	CButtonUI* pPlay;
	CButtonUI* pFast;
	CLabelUI* pBeginTime;
	CLabelUI* pEndTime;
	CSliderUI* pSlider;

	int m_nRate;

	//Option bt BkImage
	LPCTSTR sPlayFocusedImg;
	LPCTSTR sPlayNoFocusImg;
	LPCTSTR sStopFocusedImg;
	LPCTSTR sStopNoFocusImg;

	int timeCnt;
};