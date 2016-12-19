#pragma once

#include "Device\Port.h"


class CPortManager
{
private:
	CPortManager();
	~CPortManager();


public:
	static CPortManager* GetInstance();

	CPort* GetPortAt(int pos);


private:
	CPort  mPorts[PORT_MAX_NUM];
};
