
// stdafx.cpp : 只包括标准包含文件的源文件
// ColdEyes.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


/** 将 4 字节IP 转换为字符数组格式
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



/** 将6字节的mac转换为字符数组格式
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






