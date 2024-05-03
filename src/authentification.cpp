#include "../inc/authentification.h"
#include <string>
#include <functional>

using std::string;

void Authentification::SignUp()
{
	char* zErrMsg = 0;
	string sql;

	int rc;
	int user_type;
	string ans;
	bool done = false;
	while (!done)
	{
		cout << "Choose user type:\n";

		sql = "SELECT * FROM user_type";
		rc = sqlite3_exec(db, sql.c_str(), callback_user_type, 0, &zErrMsg);
		SQL_Error(rc, zErrMsg);


		cin >> ans;
		if (ans == "/exit")
			return;

		user_type = std::stoi(ans);
		if (user_type >= 1 && user_type <= 3)
		{
			done = 1;
		}
		else
			def();
	}

	string surname, password;
	while (true)
	{
		cout << "Enter your surname:\n";
		cin >> surname;
		if (surname == "/exit")
			return;

		cout << "Enter your password:\n";
		cin >> password;
		if (password == "/exit")
			return;

		if (CanSignUp(surname, password))
		{
			break;
		}
		else
		{
			cout << "This user is already exists\n";
		}
	}

	sql = "INSERT INTO users (user_type, surname, password) VALUES (?, ?, ?);";

	sqlite3_stmt* res;
	rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	if (rc == SQLITE_OK) {
		sqlite3_bind_int(res, 1, user_type);
		sqlite3_bind_text(res, 2, surname.c_str(), -1, 0);
		sqlite3_bind_text(res, 3, password.c_str(), -1, 0);
	}
	else {
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
	}

	sqlite3_step(res);
	sqlite3_finalize(res);

	this->user_type = user_type;
	this->surname = surname;

	cout << '\n';
}

bool Authentification::CanSignUp(std::string surname, std::string password)
{
	std::string sql = "SELECT * FROM users WHERE surname = ? and password = ?;";
	sqlite3_stmt* res;
	int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

	if (rc == SQLITE_OK) {
		sqlite3_bind_text(res, 1, surname.c_str(), -1, 0);
		sqlite3_bind_text(res, 2, password.c_str(), -1, 0);
	}
	else {
		std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
	}

	int step = sqlite3_step(res);
	sqlite3_finalize(res);
	if (step != SQLITE_ROW) {
		return true;
	}

	return false;
}

void Authentification::LogIn()
{
	string password;
	string sql;
	int rc;
	int* user_type = new int(0);
	string surname;
	while (true)
	{
		cout << "Enter your surname:\n";
		cin >> surname;
		if (surname == "/exit")
			return;
		cout<<"Enter your password:\n";
		cin >> password;
		sql = "SELECT * FROM users WHERE surname = ? and password = ?;";
		sqlite3_stmt* res;
		rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);

		if (rc == SQLITE_OK) {
			sqlite3_bind_text(res, 1, surname.c_str(), -1, 0);
			sqlite3_bind_text(res, 2, password.c_str(), -1, 0);
		}
		else {
			std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << '\n';
		}

		int step = sqlite3_step(res);
		if (step != SQLITE_ROW) {
			cout << "Wrong surname or password. Try again.\n";
			sqlite3_finalize(res);
			continue;
		}

		*user_type = sqlite3_column_int(res, 1);
		sqlite3_finalize(res);
		this->user_type = *user_type;
		this->surname = surname;
		break;
	}
}


void Authentification::loop()
{
	while (true)
	{
		std::vector<std::string> conditions = { "Log In", "Sign Up", "Terminate", "Clear" };


		printf("Log In Action:\n");
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
				if (!err)exit(err);
				else throw err;	
			}

			break;
		}
		else
		{
			def();
		}
	}
}

Authentification::~Authentification() {}

Authentification::Authentification(sqlite3* db) : Database(db) {}