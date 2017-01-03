#pragma once
#include "stdafx.h"
#include "stdint.h"


typedef struct USBFlashDiskStatus
{
	uint64_t mSpaceLeft;//字节
	uint64_t mSpacetotal;
}USBFlashDiskStatus;

enum CopyType {
	CopyACamera = 0,
	CopyADay,
	CopyAFile,
};

class CExHardDrive
{
	~CExHardDrive();
private:
	CExHardDrive();
	USBFlashDiskStatus* mPStatus;
	bool mIsInsert;
	bool mCancelCopy;
	HWND mHOwner;
	CString mDiskName;
	CString mUpDateFilePath;
	CString mCopyFromPath;
	CString mCopyToPath;
	UINT mRecordType;
	UINT mCameraId;
	CopyType mCopyType;

	HANDLE mEndEvent;
	HANDLE mUpdataEvent;
	HANDLE mCopyEvent;
	HANDLE mScanEvent;
	HANDLE mHEventArray[4];

	UINT mIsThreadAlive; //线程有没有启动
	CWinThread* mThread;

	ULONGLONG mTotalFileSize;
	ULONGLONG mTotalBytesTransferred;

	CTime mCopyTime;

	CTime mCopyTimeBeginDay;
	CTime mCopyTimeEndDay;

	static UINT ExHardDriveThread(LPVOID pParam);
	BOOL FindUpdataFile(CString path);
	BOOL RecordFilePath(CString path, CString FileName);

	static DWORD CALLBACK CopyProgressCall(LARGE_INTEGER TotalFileSize,
		LARGE_INTEGER TotalBytesTransferred,
		LARGE_INTEGER StreamSize,
		LARGE_INTEGER StreamBytesTransferred,
		DWORD dwStreamNumber,
		DWORD dwCallbackReason,
		HANDLE hSourceFile,
		HANDLE hDestinationFile,
		LPVOID lpData);

	USBFlashDiskStatus mDiskStatus;
public:
	static CExHardDrive* GetInstance()
	{
		static CExHardDrive ins;
		return &ins;
	}
	BOOL Init(CString diskname);

/**************************/
	BOOL StartMonitoring();
	/***********/
	BOOL EndThread();
	BOOL GetStatus(USBFlashDiskStatus *pStaus);
	BOOL Updata();
	bool CopyRecord(HWND hwnd, int type, int CameraId, int year, int month, int day, int hour, int minute, int second);
	bool CopyRecord(HWND hwnd, int type, int CameraId, int year, int month, int day);
	bool CopyRecord(HWND hwnd, int type, int CameraId);
	BOOL IsInsert();
	BOOL FindUpdataPath();
	void CancelCopy();
	/******************/
	BOOL ScanDisk(CWnd *pOwner);
	void CheckCopyFolder();

};

