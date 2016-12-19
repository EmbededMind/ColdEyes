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


