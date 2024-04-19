#ifndef OWNER_H
#define OWNER_H

#define _CRT_SECURE_NO_WARNINGS
//#define C_TYPE2 void (*) (void*, void*)
//#define C_TYPE1 void (*) (void*)

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>
#include "database.h"

//using std::cout;
//using std::cin;

class Owner: public Database
{
private:
	std::string surname;
	void (Database::* functions[4])() = { &Database::Select4, &Database::Select1,  &Database::terminate, &Database::clear };

public:
	Owner(sqlite3* db, std::string surname = "*");
	void Select4() override;
	void Select1() override;
};

using MethodPointer = void (Owner::*)();

#endif