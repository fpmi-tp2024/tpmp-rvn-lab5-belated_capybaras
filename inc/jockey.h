#ifndef JOCKEY_H
#define JOCKEY_H

#define _CRT_SECURE_NO_WARNINGS
//#define C_TYPE2 void (*) (void*, void*)
//#define C_TYPE1 void (*) (void*)

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>
#include "database.h"

class Jockey : public Database
{
private:
	std::string surname;
	void (Database::* functions[4])() = { &Database::Select3, &Database::Select6,  &Database::terminate, &Database::clear };

public:
	Jockey(sqlite3* db, std::string surname = "*");
	void Select3() override;
	void Select6() override;
};

#endif