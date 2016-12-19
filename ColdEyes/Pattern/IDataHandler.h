#pragma once

class IDataHandler
{
public:
	virtual void HandleData(UINT8* pData, size_t length) = 0;
};
