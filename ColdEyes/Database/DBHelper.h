#pragma once
#include "Database\sqlitewrapper.h"

#include "Config\SystemConfig.h"


class CDBHelper
{
private:
	CDBHelper(){};
	~CDBHelper(){};
	CDBHelper(const CDBHelper& instance){}


	SQLiteWrapper sqlite;

public:
	static CDBHelper& GetInstance();	
	bool   Insert(char* tab, char* format, ...);
	bool   Insert(char* tab, int n, ...);
	bool   OpenDatabase(char * dbFileName);
	void   Update(char* tab, char* context);
	void   Update(char* tab, char* context, char* condition);
	SQLiteStatement* Query(char* tab, char* target);
	SQLiteStatement* Query(char* tab, char* target, char* condition);
};


