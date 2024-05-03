#ifndef DATABASE_H
#define DATABASE_H

#define _CRT_SECURE_NO_WARNINGS
//#define C_TYPE2 void (*) (void*, void*)
//#define C_TYPE1 void (*) (void*)

#include <sqlite3.h>
#include <iostream>
#include <vector>

using std::cout;
using std::cin;

class Database
{
protected:
	sqlite3* db;

	int user_type;
	std::string surname;

	static int callback_user_type(void* data, int argc, char** argv, char** azColName);
	static int callback(void* data, int argc, char** argv, char** azColName);

public:
	virtual void SignUp();
	virtual void LogIn();
	Database(sqlite3* db, int type = 0);
	virtual void loop();

	virtual void Select4();
	virtual void Select1();
	virtual void Insert();
	virtual void Update();
	virtual void Delete();
	virtual void Select5();
	virtual void SelectAllOutRaces();
	virtual void Select2();
	virtual void prize_pool();
	virtual void divide_prize(double);
	virtual void Select3();
	virtual void Select6();

	virtual int getUserType()const;
	virtual std::string getSurname()const;

	virtual void clear();
	virtual void def();
	virtual void terminate();

	static void SQL_Error(int rc, char* zErrMsg);

	~Database();
};

#endif