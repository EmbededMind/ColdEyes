
// ColdEyes.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "Com\Router.h"


// CColdEyesApp: 
// �йش����ʵ�֣������ ColdEyes.cpp
//

class CColdEyesApp : public CWinApp
{
public:
	CColdEyesApp();


	CRouter  mRouter;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CColdEyesApp theApp;