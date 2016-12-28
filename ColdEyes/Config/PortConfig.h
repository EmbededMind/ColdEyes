#pragma once

//#include "Device\Port.h"

class CPortConfig
{
	friend class CPort;

public:
	UINT16               mNameId;
	UINT16               mVol;
	bool                 mIsCameraOn;
	bool                 mIsRecordEnabled;
	bool                 mIsAutoWatchEnabled;
};
