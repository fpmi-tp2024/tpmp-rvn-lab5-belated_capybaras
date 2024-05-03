#define _CRT_SECURE_NO_WARNINGS

#include "../inc/admin.h"

Admin::Admin(sqlite3* db): Database(db, 3)
{
	while (true)
	{
		std::vector<std::string> conditions = { "Insert Race", "Update Race", "Delete Race", "Output Races", "Select Best Horse",
			"Select Best Jockey", "Divide Prize Pool", "Terminate", "Clear" };


		cout << "Admin Action:\n";
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

Admin::Admin(sqlite3* db, std::string): Admin(db) {}

void Admin::prize_pool()
{
	double prize = 0;
	cout << "Input prize pool: ";
	do
	{
		cin >> prize;
		if (cin.fail())
		{
			def();
		}
	} while (cin.fail());

	divide_prize(prize);
	cout << "\n\n";
}

void Admin::divide_prize(double prize)
{

	double	first = 0.5 * prize,
		second = 0.3 * prize,
		third = 0.2 * prize;

	cout << "1st place: " << first << '\n';
	cout << "2st place: " << second << '\n';
	cout << "3st place: " << third << '\n';
}

void Admin::Insert() {
	std::string sql = "INSERT INTO races (date, race_number, horse_id, jockey_id, taken_place)\n"
		"VALUES (?, ?, ?, ?, ?);";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	std::string date;
	int race_number, horse_id, jockey_id, taken_place;
	cout << "Enter date:\n";
	cin >> date;
	if (date == "/exit")
		return;
	cout << "Enter race number:\n";
	cin >> race_number;
	horse_id = protected_horse_id();
	if (horse_id == -1)
		return;
	jockey_id = protected_jockey_id();
	if (jockey_id == -1)
		return;

	cout << "Enter taken_place:\n";
	cin >> taken_place;
	if (rc == SQLITE_OK)
	{
		sqlite3_bind_text(res, 1, date.c_str(), -1, 0);
		sqlite3_bind_int(res, 2, race_number);
		sqlite3_bind_int(res, 3, horse_id);
		sqlite3_bind_int(res, 4, jockey_id);
		sqlite3_bind_int(res, 5, taken_place);
	}
	else 
	{
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
	}

	sqlite3_step(res);
	sqlite3_finalize(res);
}

void Admin::Update() {
	std::string sql = "UPDATE races SET date=?, race_number=?, horse_id=?, jockey_id=?, taken_place=?\n"
		"WHERE id=?;";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	std::string date, id;
	int race_number, horse_id, jockey_id, taken_place;
	cout<<"Enter id:\n";
	cin >> id;
	if (id == "/exit")
		return;

	cout << "Enter date:\n";
	cin >> date;
	cout << "Enter race number:\n";
	cin >> race_number;
	cout << "Enter horse id:\n";
	cin>> horse_id;
	cout << "Enter jockey id:\n";
	cin >> jockey_id;
	cout << "Enter taken_place:\n";
	cin >> taken_place;
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(res, 1, date.c_str(), -1, 0);
		sqlite3_bind_int(res, 2, race_number);
		sqlite3_bind_int(res, 3, horse_id);
		sqlite3_bind_int(res, 4, jockey_id);
		sqlite3_bind_int(res, 5, taken_place);
		sqlite3_bind_int(res, 6, stoi(id));
	}
	else 
	{
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
	}

	sqlite3_step(res);
	sqlite3_finalize(res);
}

void Admin::Delete() {
	std::string sql = "DELETE FROM races WHERE id = ?;";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	std::string id = "0";
	cout << "Enter id:\n";
	cin >> id;
	if (id == "/exit")
		return;

	if (rc == SQLITE_OK) {
		sqlite3_bind_int(res, 1, stoi(id));
	}
	else {
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
	}
	sqlite3_step(res);
	sqlite3_finalize(res);
}

int Admin::protected_horse_id()
{
	while (true)
	{
		cout << "Enter horse id:\n";

		std::string ans = "0";
		cin >> ans;
		if (ans == "/exit")
			return -1;

		int horse_id = stoi(ans);

		std::string sql = "SELECT id FROM horses WHERE id = ?";
		sqlite3_stmt* res;
		int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

		if (rc == SQLITE_OK) {
			sqlite3_bind_int(res, 1, horse_id);
		}
		else {
			std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
		}

		int step = sqlite3_step(res);
		if (step != SQLITE_ROW)
		{
			cout << "No such horse :/\n";
		}
		else
		{
			sqlite3_finalize(res);
			return horse_id;
		}

		sqlite3_finalize(res);
	}

}

int Admin::protected_jockey_id()
{
	while (true)
	{
		cout << "Enter jockey id:\n";

		std::string ans = "0";
		cin >> ans;
		if (ans == "/exit")
			return -1;

		int jokcey_id = stoi(ans);

		std::string sql = "SELECT id FROM jockeys WHERE id = ?";
		sqlite3_stmt* res;
		int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

		if (rc == SQLITE_OK) {
			sqlite3_bind_int(res, 1, jokcey_id);
		}
		else {
			std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
		}

		int step = sqlite3_step(res);
		if (step != SQLITE_ROW)
		{
			cout << "No such jokcey :/\n";
		}
		else
		{
			sqlite3_finalize(res);
			return jokcey_id;
		}

		sqlite3_finalize(res);
	}
}


void Admin::SelectAllOutRaces()
{
	std::string	sql = "SELECT horses.id, name, age, horses.experience, price, races.date as races_date,"
			"surname as jockey_surname, jockeys.experience, year_of_birthday, address\n"
			"FROM (SELECT *, max(victory_count) FROM (SELECT owner_horses.id, name, age, experience, price, count(*) as victory_count FROM races\n"
			"INNER JOIN horses as owner_horses \n"
			"WHERE taken_place=1 and horse_id=owner_horses.id GROUP BY owner_horses.id)) as horses\n"
			"INNER JOIN races\n"
			"INNER JOIN jockeys\n"
			"WHERE horses.id =races.horse_id and races.jockey_id = jockeys.id;";

	char* zErrMsg = 0;
	int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		cout << "This owner has no winning horses\n";
	}

	SQL_Error(rc, zErrMsg);
}

void Admin::Select2() {
	char* zErrMsg = 0;
	std::string sql = "SELECT id, surname, experience, year_of_birthday, address, races_number FROM jockeys\n"
		"INNER JOIN (SELECT jockey_id, max(races_count) as races_number "
		"FROM (SELECT jockey_id, count(jockey_id) as races_count FROM races GROUP BY jockey_id))\n"
		"WHERE jockey_id=jockeys.id;";

	int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
	SQL_Error(rc, zErrMsg);
}

void Admin::Select5() {
	std::string sql = "SELECT races.id, date, race_number, horse_id, name, age, experience, owner, price, jockey_id, taken_place FROM \n"
		"(SELECT *, (substr(date,1,4)||'-'||substr(date,6,2)||'-'||substr(date,9,2)) as true_date FROM races) as races\n"
		"INNER JOIN horses\n"
		"WHERE horse_id=horses.id and true_date>=? and true_date<=?";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	char period_beginning[12], period_end[12];
	int month, day, year;
	cout << "Select races from (year month day): ";
	cin >> year >> month >> day;
	sprintf(period_beginning, "%04d-%02d-%02d", year, month, day);

	cout << "Select races untill (year month day): ";
	cin >> year >> month >> day;
	sprintf(period_end, "%04d-%02d-%02d", year, month, day);

	if (rc == SQLITE_OK)
	{
		sqlite3_bind_text(res, 1, period_beginning, -1, 0);
		sqlite3_bind_text(res, 2, period_end, -1, 0);
	}
	else
	{
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
	}

	int step = sqlite3_step(res);
	if (step != SQLITE_ROW) {
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