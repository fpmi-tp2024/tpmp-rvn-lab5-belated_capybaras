#ifndef AUTHENTIFICATION_H
#define AUTHENTIFICATION_H

#define _CRT_SECURE_NO_WARNINGS
//#define C_TYPE2 void (*) (void*, void*)
//#define C_TYPE1 void (*) (void*)

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include "database.h"

using std::cout;
using std::cin;

class Authentification: public Database
{
private:
	void (Database::* functions[4])() = { &Database::LogIn, &Database::SignUp,  &Database::terminate, &Database::clear };

public:
	void SignUp() override;
	void LogIn() override;
	Authentification(sqlite3* db);
	void loop() override;
	bool CanSignUp(std::string surname, std::string password);

	//int getUserType()const override;
	//std::string getSurname()const override;

	~Authentification();
};

#endif