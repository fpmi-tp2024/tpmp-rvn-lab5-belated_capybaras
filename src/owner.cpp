#define _CRT_SECURE_NO_WARNINGS

#include "../inc/owner.h"
#include <functional>

void Owner::Select1()
{

	std::string sql = "SELECT horses.id, name, age, horses.experience, price, races.date as races_date,"
		"surname as jockey_surname, jockeys.experience, year_of_birthday, address\n"
		"FROM (SELECT *, max(victory_count) FROM (SELECT owner_horses.id, name, age, experience, price, count(*) as victory_count FROM races\n"
		"INNER JOIN (SELECT * FROM horses WHERE owner=?) as owner_horses \n"
		"WHERE taken_place=1 and horse_id=owner_horses.id GROUP BY owner_horses.id)) as horses\n"
		"INNER JOIN races\n"
		"INNER JOIN jockeys\n"
		"WHERE horses.id =races.horse_id and races.jockey_id = jockeys.id;";

	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	if (rc == SQLITE_OK && surname != "*") {
		sqlite3_bind_text(res, 1, surname.c_str(), -1, 0);
	}
	else {
		fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
	}

	int step = sqlite3_step(res);
	if (step != SQLITE_ROW) {
		cout << "This owner has no winning horses\n";
	}
	while (step == SQLITE_ROW)
	{
		for (int i = 0; i < sqlite3_column_count(res); ++i)
		{
			cout<<sqlite3_column_name(res, i) << " = " << sqlite3_column_text(res, i) << '\n';
		}

		cout << '\n';
		step = sqlite3_step(res);
	}

	sqlite3_finalize(res);
}


void Owner::Select4() {
	std::string sql = "SELECT horse_id, name, age, experience, price, date, taken_place FROM\n"
		"(SELECT * FROM horses WHERE owner = ?) as owner_horses\n"
		"INNER JOIN races\n"
		"WHERE horse_id = owner_horses.id;";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	if (rc == SQLITE_OK) {
		sqlite3_bind_text(res, 1, surname.c_str(), -1, 0);
	}
	else {
		fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
	}

	int step = sqlite3_step(res);
	if (step != SQLITE_ROW) {
		cout<<"This owner has no horses\n";
	}
	while (step == SQLITE_ROW)
	{
		for (int i = 0; i < sqlite3_column_count(res); ++i)
		{
			cout << sqlite3_column_name(res, i) << " = " << sqlite3_column_text(res, i) << '\n';
		}

		cout << '\n';
		step = sqlite3_step(res);
	}

	sqlite3_finalize(res);
}


Owner::Owner(sqlite3* db, std::string surname): Database(db, 1)
{
	while (true)
	{
		std::vector<std::string> conditions = { "My Horses and Races", "My Best Horse", "Terminate", "Clear" };

		printf("Owner Action:\nSelect:\n");
		for (int i = 1; i <= conditions.size(); i++)
		{
			cout << std::to_string(i) + ". " + conditions[i - 1] + '\n';
		}

		int choice = 10;
		cin >> choice;
		if (cin.fail())
		{
			def();
			continue;
		}

		this->surname = surname;

		if (choice >= 1 && choice <= conditions.size())
		{
			try
			{
				std::invoke(functions[choice - 1], this);
			}
			catch (int err)
			{
				if (!err)break;
				else throw err;
			}
		}
		else
		{
			def();
		}
	}
}