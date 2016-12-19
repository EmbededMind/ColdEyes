#pragma once
#include "stdafx.h"
#include "NetSdk\netsdk.h"

class CCameraManager 
{
public:
	CCameraManager();
	~CCameraManager();


	bool          Init();


private:
	UINT          mThreadPid;
	HANDLE        mThreadHandle;
	bool          mIsThreadAlive;
};
