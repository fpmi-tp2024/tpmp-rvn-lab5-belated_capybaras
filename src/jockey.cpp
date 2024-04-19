#include "../inc/jockey.h"

Jockey::Jockey(sqlite3* db, std::string surname): Database(db, 2)
{
	while (true)
	{
		std::vector<std::string> conditions = { "My Races", "My Races in period", "Terminate", "Clear" };

		cout << "Jockey Action:\nSelect:\n";
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

void Jockey::Select3()
{
	std::string sql = "SELECT date, horse_id, name, age, experience, owner, price, taken_place FROM races\n"
		"INNER JOIN (SELECT id FROM jockeys WHERE surname=?) as jockey\n"
		"INNER JOIN horses\n"
		"WHERE jockey_id = jockey.id and horse_id = horses.id;";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	if (rc == SQLITE_OK) {
		sqlite3_bind_text(res, 1, surname.c_str(), -1, 0);
	}
	else {
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
	}

	int step = sqlite3_step(res);
	if (step != SQLITE_ROW)
	{
		cout << "This jockey didn't participate in the races\n";
	}

	while (step == SQLITE_ROW) {
		for (int i = 0; i < sqlite3_column_count(res); ++i)
		{
			cout << sqlite3_column_name(res, i) << " = " << sqlite3_column_text(res, i) << '\n';
		}
		
		cout << '\n';
		step = sqlite3_step(res);
	}

	sqlite3_finalize(res);
}

void Jockey::Select6() {
	std::string sql = "SELECT races.id, date, race_number, horse_id, taken_place, true_date FROM \n"
		"(SELECT *, (substr(date,1,4)||'-'||substr(date,6,2)||'-'||substr(date,9,2)) as true_date FROM races) as races\n"
		"INNER JOIN (SELECT id as id_jockey FROM jockeys WHERE surname = ?)\n"
		"WHERE jockey_id=id_jockey and true_date>=? and true_date<=?";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	char period_beginning[12], period_end[12];
	int month, day, year;
	cout<<"Select races from (year month day): ";
	cin >> year >> month >> day;
	sprintf(period_beginning, "%04d-%02d-%02d", year, month, day);

	cout << "Select races untill (year month day): ";
	cin >> year >> month >> day;
	sprintf(period_end, "%04d-%02d-%02d", year, month, day);

	if (rc == SQLITE_OK)
	{
		sqlite3_bind_text(res, 1, surname.c_str(), -1, 0);
		sqlite3_bind_text(res, 2, period_beginning, -1, 0);
		sqlite3_bind_text(res, 3, period_end, -1, 0);
	}
	else {
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
	}

	int step = sqlite3_step(res);
	if (step != SQLITE_ROW)
	{
		cout << "There were no races during this period\n";
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