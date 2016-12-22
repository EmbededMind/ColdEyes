#include "stdafx.h"
#include "Database\DBHelper.h"
#include <string>


#define DBCOL_BOATNAME                0
#define DBCOL_BRT                     1
#define DBCOL_VOL                     2
#define DBCOL_AL                      3
#define DBCOL_AW                      4
#define DBCOL_AWBT                    5
#define DBCOL_AWET                    6
#define DBCOL_AS                      7
#define DBCOL_ASID                    8
#define DBCOL_ASDS                    9
#define DBCOL_ASS                    10




CDBHelper& CDBHelper::GetInstance()
{
	static CDBHelper mInstance;
	return mInstance;
}



//void CDBHelper::Insert(char* tab, char* values)
//{
//	char sqlStmt[128];
//
//	sprintf_s(sqlStmt, "INSERT INTO %s VALUES(%s);", tab, values);
//
//	if (!sqlite.DirectStatement(sqlStmt)) {
//		Print("Sql error:%s", sqlStmt);
//	}
//}
bool CDBHelper::Insert(char* tab, char* format, ...)
{
	char formatValues[100];
	char sqlStmt[128];
	va_list args;
	va_start(args, format);

	vsnprintf_s(formatValues,100, format, args);

	va_end(args);

	sprintf_s(sqlStmt, "INSERT INTO %s VALUES(%s);", tab, formatValues);

	if (sqlite.DirectStatement(sqlStmt)) {
		return true;
	}
	else {
		Print("Sql error:%s\n format values:%s", sqlStmt,formatValues);
		return false;
	}
}



bool CDBHelper::Insert(char* tab, int n, ...)
{
	return false;
}



bool CDBHelper::OpenDatabase(char* dbFileName)
{
	if (sqlite.Open(dbFileName)) {		
		return true;
	}
	Print("Database %s open failed", dbFileName);
	return true;
}



void CDBHelper::Update(char* tab, char* context)
{
	char sqlStmt[128];

	sprintf_s(sqlStmt,"UPDATE %s SET %s;", tab,  context);

	if (!sqlite.DirectStatement(sqlStmt)) {
		Print("Sql error:%s", sqlStmt);
	}
}



SQLiteStatement* CDBHelper::Query(char* tab, char* target)
{
	char sqlStmt[128];

	sprintf_s(sqlStmt, "SELECT %s FROM %s;", target, tab);

	return sqlite.Statement(sqlStmt);
}



SQLiteStatement* CDBHelper::Query(char* tab, char* target, char* condition)
{
	char sqlStmt[128];

	if (condition ) {
		sprintf_s(sqlStmt, "SELECT %s FROM %s WHERE %s;",target, tab, condition);
	}
	else {
		sprintf_s(sqlStmt, "SELECT %s FROM %s;", target, tab);
	}
	
	return sqlite.Statement(sqlStmt);	
}