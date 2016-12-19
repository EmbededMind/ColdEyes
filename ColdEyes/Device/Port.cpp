#include "stdafx.h"
#include "Device\Port.h"

CPort::CPort()
{

}



CPort::~CPort()
{

}



UINT16 CPort::GetId()
{
	return this->mId;
}



char* CPort::GetMac()
{
	return this->mMac;
}



UINT16 CPort::GetNameIndex()
{
	return this->mNameIndex;
}



void CPort::SetId(UINT16 id)
{
	this->mId   = id;
}



void CPort::SetMac(char* mac)
{
	strcpy_s(mMac, mac);
}



void CPort::SetNameIndex(UINT16 inx)
{
	this->mNameIndex  = inx;
}
