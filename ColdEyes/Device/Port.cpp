#include "stdafx.h"
#include "Device\Port.h"


CString PortName[24] = {  //��Ӧ����id
	_T("�����1"),
	_T("�����2"),
	_T("�����3"),
	_T("�����4"),
	_T("�����5"),
	_T("�����6"),
	_T("��ͷ�����"),
	_T("���װ������"),
	_T("�����������"),
	_T("�����������"),
	_T("���������"),
	_T("�����������"),
	_T("����̨�����"),
	_T("���̨�����"),
	_T("�����������"),
	_T("��Ա�������"),
	_T("�����������"),
	_T("������������"),
	_T("�޾��װ������"),
	_T("һ��װ������"),
	_T("����װ������"),
	_T("����װ������"),
	_T("�Ĳ�װ������"),
	_T("���װ������")
};


CPort::CPort()
{

}



CPort::~CPort()
{

}



void  CPort::BindCamera(CCamera* pCamera)
{
	this->mCamera  = pCamera;
}



CCamera* CPort::GetBindedCamera()
{
	return this->mCamera;
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

CString & CPort::GetName()
{
	return PortName[mNameIndex - 1];
}

