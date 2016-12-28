#pragma once

#include "stdafx.h"

#include "Device\Camera.h"
#include "Config\PortConfig.h"

class CPort
{
public:
	CPort();
	~CPort();


public:
	CPortConfig  mConfig;
	UINT16       mPos;

	void         BindCamera(CCamera* pCamera);

	void         CommitUpdate();

	CCamera*     GetBindedCamera();
	UINT16		 GetId();
	char*		 GetMac();
	UINT16		 GetNameIndex();


	
	void		 SetId(UINT16 id);
	void		 SetMac(char* mac);
	void		 SetNameIndex(UINT16 inx);





private:
	UINT16      mId;

	UINT16      mNameIndex;
	char        mMac[20];

	CCamera*    mCamera;

};