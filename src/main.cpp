#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <sqlite3.h>

#include "../inc/authentification.h"
#include "../inc/jockey.h"
#include "../inc/admin.h"
#include "../inc/owner.h"
#include <functional>

Database* createAdmin(sqlite3* db, std::string sur)
{
	return new Admin(db, sur);
}

Database* createJockey(sqlite3* db, std::string sur)
{
	return new Jockey(db, sur);
}

Database* createOwner(sqlite3* db, std::string sur)
{
	return new Owner(db, sur);
}


int main() {
	const char* db_path = "hippodrome.db";
	sqlite3* db;
	int rc = sqlite3_open(db_path, &db);
	if (rc)
	{
		std::cerr << "cannot open database\n";
		return 0;
	}
	
	Authentification* auth = new Authentification(db);
	Database*(*create[])(sqlite3*, std::string) = { createOwner, createJockey, createAdmin };
	while (true)
	{
		auth->loop();
		if (auth->getUserType()>=1 && auth->getUserType() <= 3)
		{
			Database* obj = create[auth->getUserType() - 1](db, auth->getSurname());
		}
	}

	delete auth;
	sqlite3_close(db);
	return 0;
}