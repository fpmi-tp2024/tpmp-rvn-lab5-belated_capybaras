#ifndef ADMIN_H
#define ADMIN_H

#define _CRT_SECURE_NO_WARNINGS
//#define C_TYPE2 void (*) (void*, void*)
//#define C_TYPE1 void (*) (void*)

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>
#include "database.h"

class Admin : public Database
{
private:
	//MethodPointer functions[9] = { &(Database::Insert), &(Database::Update),  &(Database::Delete), &(Database::Select5),  &(Database::SelectAllOutRaces),
	//	&(Database::Select2), &(Database::prize_pool), &(Database::terminate), &(Database::clear) };
	void (Database::* functions[9])() = { &Database::Insert, &Database::Update,  &Database::Delete, &Database::Select5,  &Database::SelectAllOutRaces,
			&Database::Select2, &Database::prize_pool, &Database::terminate, &Database::clear };

	int protected_horse_id();
	int protected_jockey_id();

public:
	Admin(sqlite3* db);
	Admin(sqlite3* db, std::string);
	void Insert() override;
	void Update() override;
	void Delete() override;
	void Select5() override;
	void SelectAllOutRaces() override;
	void Select2() override;
	void prize_pool() override;
	void divide_prize(double) override;

};


#endif