
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// ColdEyes.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


/** �� 4 �ֽ�IP ת��Ϊ�ַ������ʽ
 *
 */
void IPNumberToStr(UINT8* pData, char* ip)
{
	int tmp = 0;
	for (int i = 0; i < 4; i++) {
		tmp += sprintf_s(ip + tmp, 4, "%d", pData[i]);
		if (i < 3) {
			ip[tmp] = '.';
			tmp++;
		}
	}
}



/** ��6�ֽڵ�macת��Ϊ�ַ������ʽ
 *
 */
void MacNumberToStr(UINT8* pNumber, char* pMac)
{
	int tmp = 0;
	int i = 0;
	for (; i < 6; i++) {
		tmp = pNumber[i] / 16;
		if (tmp < 10) {
			pMac[i * 3] = tmp + '0';
		}
		else {
			pMac[i * 3] = tmp - 10 + 'a';
		}

		tmp = pNumber[i] % 16;
		if (tmp < 10) {
			pMac[i * 3 + 1] = tmp + '0';
		}
		else {
			pMac[i * 3 + 1] = tmp - 10 + 'a';
		}
	}

	pMac[2] = ':';
	pMac[5] = ':';
	pMac[8] = ':';
	pMac[11] = ':';
	pMac[14] = ':';
	pMac[17] = 0;
}






