#pragma once

#include "stdafx.h"

class CPort
{
public:
	CPort();
	~CPort();


public:
	UINT16		 GetId();
	UINT16		 GetNameIndex();
	char*		 GetMac();

	void		 SetId(UINT16 id);
	void		 SetNameIndex(UINT16 inx);
	void		 SetMac(char* mac);




private:
	UINT16     mId;
	UINT16     mNameIndex;
	char       mMac[20];
};