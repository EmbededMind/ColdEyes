#pragma once

#include "stdafx.h"

#include "Device\Camera.h"

class CPort
{
public:
	CPort();
	~CPort();


public:

	void         BindCamera(CCamera* pCamera);

	CCamera*     GetBindedCamera();
	UINT16		 GetId();
	char*		 GetMac();
	UINT16		 GetNameIndex();


	
	void		 SetId(UINT16 id);
	void		 SetMac(char* mac);
	void		 SetNameIndex(UINT16 inx);





private:
	UINT16     mId;
	UINT16     mNameIndex;
	char       mMac[20];

	CCamera*   mCamera;
};