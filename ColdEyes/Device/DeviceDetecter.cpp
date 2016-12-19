#include "stdafx.h"

#include "Device\DeviceDetecter.h"
#include "Device\PortManager.h"
#include "Device\Camera.h"




UINT __stdcall LoginThread(PVOID pM)
{
	MSG msg;
	CDeviceDetecter* pThis  = (CDeviceDetecter*)pM;

	while (GetMessage(&msg, 0, 0, 0))
	{
		switch (msg.message)
		{
			case USER_MSG_SCAN_DEV:
				{
					Print("Searching mac %s", pThis->mPendedMac[msg.wParam - 1]);
					char* sMac  = (char*)msg.lParam;
					int    retByteLength;
					BOOL ret  = H264_DVR_SearchDevice( (char*)pThis->mDeviceNetConfig, 10, &retByteLength, 5000);

					if (ret) {
						pThis->mLastScanedDeviceNumber  = retByteLength / sizeof(SDK_CONFIG_NET_COMMON_V2);
						Print("Search %d device", pThis->mLastScanedDeviceNumber);

						SDK_CONFIG_NET_COMMON_V2* pConfig  = pThis->FindDevice(sMac);
						if ( pConfig != NULL) {
							CCamera* pNewCamera  = new CCamera();
							pNewCamera->SetCommonNetConfig(pConfig);
							CPort* pPort  = CPortManager::GetInstance()->GetPortAt(msg.wParam);
							if (pPort) {
								if (pPort->GetBindedCamera() == NULL) {
									pPort->BindCamera(pNewCamera);
									PostMessage(AfxGetMainWnd()->m_hWnd, USER_MSG_FIND_DEV, true, (LPARAM)pPort);
								}
								else {
									Print("Port at %d has camera", msg.wParam);
								}
							}
						}
					}
					else {
						Print("Search failed. Error code:%d", H264_DVR_GetLastError());
					}
				}								
				break;
			//--------------------------------------------
		}
		DispatchMessage(&msg);
	}

	return 0;
}


CDeviceDetecter::CDeviceDetecter()
{	
	memset(mDevicesState, 0, sizeof(mDevicesState));
	mLiDueTime.QuadPart  = -10000000 * TICK_ELAPSE_SEC;
}



CDeviceDetecter::~CDeviceDetecter()
{

}



bool CDeviceDetecter::CreateDetectionThread()
{
	if (mAckEvent != NULL) {
		ResetEvent(mAckEvent);
	}
	else {
		mAckEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	mDetectionThread = AfxBeginThread(DetectionThread, this);

	return (mDetectionThread != NULL);

	/*mLoginThread  = (HANDLE)_beginthreadex(NULL,  0,  LoginThread, NULL, 0, &mLoginThreadPid);*/
}



bool CDeviceDetecter::CreateLoginThread()
{
	//if (mScanDevEvent != NULL) {
	//	ResetEvent(mScanDevEvent);
	//}
	//else {
	//	mScanDevEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
	//}

	//if (mLoginDevEvent != NULL)
	//{
	//	ResetEvent(mLoginDevEvent);
	//}
	//else {
	//	mLoginDevEvent  = CreateEvent(NULL, TRUE, FALSE, NULL);
	//}


	//mLoginEventArray[0]  = mLoginEndEvent;
	//mLoginEventArray[1]  = mLoginDevEvent;
	//mLoginEventArray[2]  = mScanDevEvent;

	//mLoginThread  = AfxBeginThread(LoginThread, this);
	//return (mLoginThread != NULL);

	mLoginThread  = (HANDLE)_beginthreadex(NULL, 0, LoginThread, NULL, 0, &mLoginThreadPid);

	return (mLoginThread != 0);
}


UINT CDeviceDetecter::DetectionThread(LPVOID pParam)
{
	CDeviceDetecter * pThis = (CDeviceDetecter*)pParam;

	pThis->mIsDetectionThreadAlive = true;

	DWORD Event = 0;

	DWORD TimeoutCnt  = 0;

	if (!SetWaitableTimer(pThis->mTickTimer, &pThis->mLiDueTime, 0, NULL, NULL, FALSE)) {
		Print("SetWaitableTimer error");
		return -1;
	}

	for (;;) {
		// Wait tick timer event.
		if (WaitForSingleObject(pThis->mTickTimer, INFINITE) == WAIT_OBJECT_0) {
			// Send hand single.
			pThis->PendPortState();

			SetWaitableTimer(pThis->mTickTimer, &pThis->mLiDueTime,  0, NULL, NULL,  0);

			if (WaitForSingleObject(pThis->mAckEvent, ACK_TIMEOUT_MILLMS) == WAIT_OBJECT_0) {
				// Pump state
				Print("握手回复");
				ResetEvent(pThis->mAckEvent);
			}				
			else {
				TimeoutCnt++;
				if (TimeoutCnt > TICK_ACK_TIMEOUT_CNT) {
					Print("Exception: 103 握手超时");
					TimeoutCnt  = 0;
				}
			}
		}
	}

	return 0;
}



CDeviceDetecter* CDeviceDetecter::GetInstance()
{
	static CDeviceDetecter mInstance;
	return &mInstance;
}



void CDeviceDetecter::HandleData(UINT8* pData, size_t length)
{
	if (mIsNeedAck) {
		SetEvent(mAckEvent);
	}


	int cmd  = pData[0];
	int param  = pData[1];

	// 
	if (cmd == 0x05) {
		// 端口状态信息
		if (param == 1) {
			for (int i = 0; i < PORT_MAX_NUM; i++) {
				bool isOnline     = (pData[3] & 0x80) > 0;
				bool  isReplaced  = (pData[3] & 0x10) > 0;
				
				if (mDevicesState[i] == DevState_Offline) {
					// 检测到插入
					if (isOnline) {
						Print("---> Plug");
						mDevicesState[i]  = DevState_PendMac;

			
						// 发送请求mac的指令。
						Print("Pending mac");
					}
				}
				else if(mDevicesState[i] == DevState_Online){
					// 检测到拔出
					if ( ! isOnline) {
						Print("<--- Pull");
						mDevicesState[i]  = DevState_Offline;
						memset(mPendedMac[i], 0, 40);
					}
					// 检测到更换
					else if(isReplaced){
						Print("---- Replaced");
						mDevicesState[i]  = DevState_PendMac;
						// 发送请求mac的指令。
						Print("Pending mac");
						memset(mPendedMac[i], 0, 40);
					}
				}
				else if (mDevicesState[i] == DevState_PendMac) {
					Print("Pend mac timeout");
					mDevicesState[i]  = DevState_Offline;
				}
			}
		}
		// 端口 MAC
		else if (param == 2) {
			int pos  = pData[2];
			if (pos > 0 && pos <= 6) {
				if (mDevicesState[pos - 1] == DevState_PendMac) {
					MacNumberToStr(&pData[3], mPendedMac[pos-1]);
					mDevicesState[pos-1]  = DevState_PendCamera;

					// 新插入的摄像头在已扫描到的结果中不存在，则重新扫描。
					SDK_CONFIG_NET_COMMON_V2* pNetConfig  = FindDevice(mPendedMac[pos - 1]);
					if (pNetConfig == NULL) {
						PostThreadMessage(mLoginThreadPid, USER_MSG_SCAN_DEV, pos, (LPARAM)mPendedMac[pos-1]);
					}
					else {
						Print("Device exist :%s", mPendedMac[pos-1]);
						CPort* pPort  = CPortManager::GetInstance()->GetPortAt(pos);
						if (pPort) {
							if (pPort->GetBindedCamera() == NULL) {
								CCamera* pNewCamera  = new CCamera();
								pNewCamera->SetCommonNetConfig(pNetConfig);
								pPort->BindCamera(pNewCamera);
								PostMessage(AfxGetMainWnd()->m_hWnd, USER_MSG_FIND_DEV, true, (LPARAM)pPort);
							}
						}
					}
				}
			}
		}
	}
}




/*
UINT CDeviceDetecter::LoginThread(LPVOID p)
{
	CDeviceDetecter* pThis  = (CDeviceDetecter*)p;

	pThis->mIsLoginThreadAlive  = true;

	DWORD Event  = 0;

	for (;;) {
	   Event  = WaitForMultipleObjects(2, pThis->mLoginEventArray, FALSE, INFINITE);
	   switch (Event) {
			case 0: 
			break;

			case 1: 
			break;

			case 2: 
			{
			
				for (int i = 0; i < PORT_MAX_NUM; i++) {
					if (pThis->mDevicesState[i] == DevState_PendCamera) {

					}
				}
			}
			break;
	   }
	}

	return 0;
}
*/


void CDeviceDetecter::PendPortState()
{
	Print("Pend port state");
	mIsNeedAck  = true;
}



SDK_CONFIG_NET_COMMON_V2* CDeviceDetecter::FindDevice(char* mac)
{
	for (int i = 0; i < mLastScanedDeviceNumber; i++) {
		if (strcmp(mDeviceNetConfig[i].sMac, mac) == 0) {
			return &mDeviceNetConfig[i];
		}
	}

	return NULL;
}



bool  CDeviceDetecter::StartDetect()
{
	if (mIsDetectionThreadAlive) {
		do {
			SetEvent(mDetectionEndEvent);
		}while(mIsDetectionThreadAlive);
	}

	if (mDetectionEndEvent != NULL) {
		ResetEvent(mDetectionEndEvent);
	}
	else {
		mDetectionEndEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}

	if (mAckEvent != NULL) {
		ResetEvent(mAckEvent);
	}
	else {
		mAckEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}


	if (!CreateLoginThread()) {
		Print("Create login thread failed");
		return false;
	}



	if (!CreateDetectionThread()) {
		Print("Create detection thread failed");
		return false;
	}

	mTickTimer  = CreateWaitableTimer(NULL, TRUE, NULL);
	if (NULL == mTickTimer) {
		Print("Create tick timer failed");
		return false;
	}
}





