#pragma once

#include "DuiLib\UIlib.h"

#include "ColdEyes.h"
#include "ColdEyesDlg.h"

using namespace DuiLib;

#define MSGID_CANCEL			0
#define MSGID_OK				1
#define MSGID_RECORD			2
#define MSGID_EXHARDDRIVE_OUT	3



class CVoiceRecordMsgWnd
	:public WindowImplBase
{
public: 
	CVoiceRecordMsgWnd();
	~CVoiceRecordMsgWnd();

	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void) const;
	virtual void Notify(TNotifyUI &msg);
	virtual void InitWindow();
	virtual LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	virtual LRESULT OnSysCommand(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


private:
	CDuiString m_sSkinType;

	CLabelUI*  m_pRecordingImage;

	CLabelUI* m_pShowRecordTime;

	int m_timeCnt;

public:
	static int MessageBox(HWND hParent, LPCTSTR sSkinType, LPCTSTR text1, LPCTSTR text2, LPARAM lParam, WPARAM wParam) {
		CVoiceRecordMsgWnd* pWnd = new CVoiceRecordMsgWnd();

		pWnd->m_sSkinType = sSkinType;
		pWnd->Create(hParent, _T("msgWnd"), WS_POPUP | WS_CLIPCHILDREN, WS_EX_TOOLWINDOW);
		pWnd->CenterWindow();
		//pWnd->SetMsg(text1,text2);
		return pWnd->ShowModal();
	}

};