#include "stdafx.h"
#include "ExHardDrive.h"
#include "Database\DBHelper.h"

CExHardDrive::CExHardDrive()
{
}
CExHardDrive::~CExHardDrive()
{
	SetEvent(mEndEvent);
}
BOOL CExHardDrive::Init(CString diskname)
{
	if (mIsThreadAlive)
	{
		do
		{
			SetEvent(mEndEvent);
		} while (mIsThreadAlive);
	}
	if (mEndEvent != NULL)
		ResetEvent(mEndEvent);
	else
		mEndEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mUpdataEvent != NULL)
		ResetEvent(mUpdataEvent);
	else
		mUpdataEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mCopyEvent != NULL)
		ResetEvent(mCopyEvent);
	else
		mCopyEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (mScanEvent != NULL)
		ResetEvent(mScanEvent);
	else
		mScanEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	mHEventArray[0] = mEndEvent;
	mHEventArray[1] = mScanEvent;
	mHEventArray[2] = mCopyEvent;
	mHEventArray[3] = mUpdataEvent;

	mDiskName = diskname;
	mIsInsert = TRUE;
	mCancelCopy = false;
	CheckCopyFolder();
	return TRUE;
}

UINT CExHardDrive::ExHardDriveThread(LPVOID pParam)
{
	CExHardDrive *ExHardDrive = (CExHardDrive*)pParam;

	ExHardDrive->mIsThreadAlive = TRUE;
	DWORD Event = 0;
	for (;;)
	{
		Event = WaitForMultipleObjects(4, ExHardDrive->mHEventArray, FALSE, INFINITE);
		switch (Event)
		{
		case 0:
			Print("m_endEvent\n");
			ExHardDrive->mIsThreadAlive = FALSE;
			ResetEvent(ExHardDrive->mEndEvent);
			AfxEndThread(100);
			break;
		case 1:
			if (!ExHardDrive->FindUpdataFile(ExHardDrive->mUpDateFilePath))
			{
				ExHardDrive->mUpDateFilePath = _T("NULL");
			}
			ResetEvent(ExHardDrive->mScanEvent);
			break;
		case 2:
		{
			ResetEvent(ExHardDrive->mCopyEvent);
			//Print("before CopyFileEx");
			char sqlStmtTab[128];
			char sqlStmtTarget[128];
			char sqlStmtCon[128];
			SQLiteStatement* sqlStmtement;
			if (ExHardDrive->mCopyType == 1)
				sprintf_s(sqlStmtTab, "normal_record , totalsize");
			else
				sprintf_s(sqlStmtTab, "alarm_record , totalsize");
			sprintf_s(sqlStmtTarget,"beginsec");
			if (ExHardDrive->mCopyType == CopyACamera)
				sprintf_s(sqlStmtCon, "id == %d", ExHardDrive->mCameraId);
			else if (ExHardDrive->mCopyType == CopyADay)
				sprintf_s(sqlStmtCon, "id == %d AND beginsec >= %llu AND beginsec <= %llu", ExHardDrive->mCopyTimeBeginDay, ExHardDrive->mCopyTimeEndDay);
			else
				sprintf_s(sqlStmtCon, "id == %d AND beginsec == %llu", ExHardDrive->mCameraId, ExHardDrive->mCopyTime);
			SQLiteStatement* stmt = CDBHelper::GetInstance().Query(sqlStmtTab, sqlStmtTarget, sqlStmtCon);

			ExHardDrive->mTotalFileSize = 0;
			ExHardDrive->mTotalBytesTransferred = 0;

			while (stmt->NextRow())
			{
				ExHardDrive->mTotalFileSize += stmt->ValueInt(1);
			}

			if (!ExHardDrive->GetStatus(&ExHardDrive->mDiskStatus))
			{
				::PostMessage(ExHardDrive->mHOwner, USER_MSG_COPY_DISKOUT, NULL, NULL);
				break;
			}
			if (ExHardDrive->mDiskStatus.mSpaceLeft < ExHardDrive->mTotalFileSize)
			{
				PostMessage(ExHardDrive->mHOwner, USER_MSG_COPY_NOSPACE, NULL, NULL);
				break;
			}

			stmt->RestartSelect();

			while (stmt->NextRow())
			{
				uint64_t begin_sec;
				begin_sec = stmt->ValueInt(0);
				BOOL bSucceed = CopyFileEx(ExHardDrive->mCopyFromPath, ExHardDrive->mCopyToPath,
					(LPPROGRESS_ROUTINE)CopyProgressCall,
					ExHardDrive, NULL,
					COPY_FILE_ALLOW_DECRYPTED_DESTINATION | COPY_FILE_COPY_SYMLINK | COPY_FILE_FAIL_IF_EXISTS);
				if (ExHardDrive->mHOwner != NULL)
				{
					if (bSucceed)
					{
					}
					else
					{
						if (GetLastError() == 2) {
							if (!PathIsDirectory(ExHardDrive->mDiskName))
							{
								::PostMessage(ExHardDrive->mHOwner, USER_MSG_COPY_DISKOUT, NULL, NULL);
								break;
							}
						}
					}
					ExHardDrive->mTotalBytesTransferred += stmt->ValueInt(1);
				}
			}
			if (PathIsDirectory(ExHardDrive->mDiskName))
			{
				::PostMessage(ExHardDrive->mHOwner, USER_MSG_COPY_END, NULL, NULL);
			}
		}
			break;
		case 3:
			ExHardDrive->FindUpdataFile(ExHardDrive->mDiskName);
			ResetEvent(ExHardDrive->mUpdataEvent);
			break;
		default:
			break;
		}
	}
	return 0;
}

BOOL CExHardDrive::FindUpdataFile(CString path)
{
	CFileFind fileFinder;
	CString filePath = path + _T("*.*");

	BOOL bFinished = fileFinder.FindFile(filePath);
	while (bFinished)  //每次循环对应一个类别目录
	{
		bFinished = fileFinder.FindNextFile();
		if (fileFinder.IsDirectory() && !fileFinder.IsDots())
		{
			CString fileName = fileFinder.GetFileName();
			if (fileName == _T("haha"))
			{
				mUpDateFilePath = fileFinder.GetFilePath();
				return TRUE;
			}
			else
			{
				FindUpdataFile(fileFinder.GetFilePath() + _T("\\"));
			}
		}
		else
		{
			CString fileName = fileFinder.GetFileName();
			if (fileName == _T("hehe.txt"))
			{
				mUpDateFilePath = fileFinder.GetFilePath();
				return TRUE;
			}
		}
	}
	fileFinder.Close();
	return 0;
}

BOOL CExHardDrive::RecordFilePath(CString path, CString FileName)
{
	mCopyFromPath = path;
	if (mRecordType)
	{
		mCopyToPath = mDiskName + _T("AlarmRecord\\");
	}
	else
	{
		mCopyToPath = mDiskName + _T("NormalRecord\\");
	}
	CString tmp;
	mCopyToPath += tmp;
	mCopyToPath += FileName;
	//Print("CopyFile path : %S", mCopyToPath);
	SetEvent(mCopyEvent);
	return 0;
}

DWORD CExHardDrive::CopyProgressCall(LARGE_INTEGER TotalFileSize,
	LARGE_INTEGER TotalBytesTransferred,
	LARGE_INTEGER StreamSize,
	LARGE_INTEGER StreamBytesTransferred,
	DWORD dwStreamNumber,
	DWORD dwCallbackReason,
	HANDLE hSourceFile,
	HANDLE hDestinationFile,
	LPVOID lpData)
{
	if (((CExHardDrive*)lpData)->mCancelCopy)
	{
		((CExHardDrive*)lpData)->mCancelCopy = FALSE;
		return PROGRESS_CANCEL;
	}
	if (dwCallbackReason == CALLBACK_STREAM_SWITCH)
	{
		//发送开始文件的录制信息 , 消息号是 COPY_START
	}
	else
	{
		//((CExHardDrive*)lpData)->mTotalFileSize = TotalFileSize.QuadPart;
		//((CExHardDrive*)lpData)->mTotalBytesTransferred = TotalBytesTransferred.QuadPart;
		int n = (((CExHardDrive*)lpData)->mTotalBytesTransferred + TotalBytesTransferred.QuadPart) * 100 / ((CExHardDrive*)lpData)->mTotalFileSize;
		if(((CExHardDrive*)lpData)->mHOwner)
			::PostMessage(((CExHardDrive*)lpData)->mHOwner, USER_MSG_COPY_PRO, n, NULL);
	}
	return PROGRESS_CONTINUE;
}

BOOL CExHardDrive::StartMonitoring()
{
	if (!mIsInsert) return 0;
	if (!(mThread = AfxBeginThread(ExHardDriveThread, this)))
		return FALSE;
	Print("Thread Start\n");
	return TRUE;
}

BOOL CExHardDrive::EndThread()
{
	mIsInsert = FALSE;
	SetEvent(mEndEvent);
	return 0;
}

BOOL CExHardDrive::GetStatus(USBFlashDiskStatus *pStaus)
{
	if (!mIsInsert) return 0;
	ULARGE_INTEGER   uiFreeBytesAvailableToCaller;
	ULARGE_INTEGER   uiTotalNumberOfBytes;
	ULARGE_INTEGER   uiTotalNumberOfFreeBytes;
	TRACE("m_scanEvent\n");
	if (GetDiskFreeSpaceExW(mDiskName,
		&uiFreeBytesAvailableToCaller,
		&uiTotalNumberOfBytes,
		&uiTotalNumberOfFreeBytes))
	{
		pStaus->mSpaceLeft = (FLOAT)((LONGLONG)uiTotalNumberOfFreeBytes.QuadPart);
		pStaus->mSpacetotal = (FLOAT)((LONGLONG)uiTotalNumberOfBytes.QuadPart);
		TRACE(_T("--%f-- %f"), pStaus->mSpaceLeft, pStaus->mSpacetotal);
	}
	return TRUE;
}

BOOL CExHardDrive::Updata()
{
	if (!mIsInsert || !mIsThreadAlive) return 0;
	SetEvent(mUpdataEvent);
	return TRUE;
}

bool CExHardDrive::CopyRecord(HWND hwnd, int type, int CameraId, int year, int month, int day, int hour, int minute, int second)
{
	if (!mIsInsert)
		return false;
	CTime time = CTime(year,month,day,hour,minute,second);
	mCopyTime = time;
	mHOwner = hwnd;
	mRecordType = type;
	mCameraId = CameraId;
	mCopyType = CopyAFile;
	return true;
}

bool CExHardDrive::CopyRecord(HWND hwnd, int type, int CameraId, int year, int month, int day)
{
	if (!mIsInsert)
		return false;
	CTime timebegin = CTime(year, month, day, 0, 0, 0);
	mCopyTimeBeginDay = timebegin;
	CTime timeend = CTime(year, month, day, 23 ,59, 59);
	mCopyTimeEndDay = timeend;
	mHOwner = hwnd;
	mRecordType = type;
	mCameraId = CameraId;
	mCopyType = CopyADay;
	return true;
}

bool CExHardDrive::CopyRecord(HWND hwnd, int type, int CameraId)
{
	if (!mIsInsert)
		return false;
	mHOwner = hwnd;
	mRecordType = type;
	mCameraId = CameraId;
	mCopyType = CopyACamera;
	return true;
}
 
BOOL CExHardDrive::IsInsert()
{
	return this->mIsInsert;
}

BOOL CExHardDrive::FindUpdataPath()
{
	if (!mIsInsert || !mIsThreadAlive) return 0;
	SetEvent(mUpdataEvent);
	return 0;
}

void CExHardDrive::CancelCopy()
{
	mCancelCopy = true;
}

BOOL CExHardDrive::ScanDisk(CWnd *pOwner)
{
	DWORD mask;
	char tch[50];
	TCHAR diskname[50];
	CString DiskName;
	UINT type;
	mask = GetLogicalDrives();

	_itoa_s(mask, tch, 2);

	for (int i = 0; i < 32; i++)
	{
		if ((mask >> i) == 1)
		{
			diskname[0] = 'A' + i;
			diskname[1] = '\0';
			wcscat_s(diskname, TEXT(":\\"));
			DiskName.Format(_T("%s"), diskname);
			type = GetDriveType(DiskName);
			if (type == DRIVE_REMOVABLE)
			{
				this->Init(DiskName);
				this->StartMonitoring();
				return true;
			}
		}
	}
	return false;
}

void CExHardDrive::CheckCopyFolder()
{
	if (!PathIsDirectory(mDiskName + _T("NormalRecord\\")))
	{
		CreateDirectory(mDiskName + _T("NormalRecord\\"), NULL);
	}
	if (!PathIsDirectory(mDiskName + _T("AlarmRecord\\")))
	{
		CreateDirectory(mDiskName + _T("AlarmRecord\\"), NULL);
	}
	CString tmp;
	for (int i = 1; i < 7; i++)
	{
		tmp.Format(_T("%d\\"), i);
		if (!PathIsDirectory(mDiskName + _T("NormalRecord\\") + tmp))
		{
			CreateDirectory(mDiskName + _T("NormalRecord\\") + tmp, NULL);
		}
		if (!PathIsDirectory(mDiskName + _T("AlarmRecord\\") + tmp))
		{
			CreateDirectory(mDiskName + _T("AlarmRecord\\") + tmp, NULL);
		}
	}
}

