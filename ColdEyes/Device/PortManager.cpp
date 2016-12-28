#include "stdafx.h"
#include "Device\PortManager.h"

CPortManager::CPortManager()
{

}



CPortManager::~CPortManager()
{

}



CPortManager* CPortManager::GetInstance()
{
	static CPortManager instance;
	return &instance;
}



UINT16 CPortManager::AllocId()
{
	bool tmp[PORT_MAX_NUM]  = {false};
	UINT16 i  = 0;
	for (i; i < PORT_MAX_NUM; i++) {
		if (mPorts[i].GetId() > 0) {
			tmp[mPorts[i].GetId()-1]  = true;
		}
	}

	for (i = 0; i < PORT_MAX_NUM; i++) {
		if (tmp[i] == false) {
			return i+1;
		}
	}

	return 0;
}



CPort* CPortManager::GetPortAt(int pos)
{
	if (pos > 0 && pos < 7) {
		return &mPorts[pos - 1];
	}
	else {
		Print("Invalid pos-->\'Get port at %d\'", pos);
		return NULL;
	}
}


