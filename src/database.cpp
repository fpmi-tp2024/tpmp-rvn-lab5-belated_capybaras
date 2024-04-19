#include "../inc/database.h"

int Database::callback_user_type(void* data, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		if (argv[i])
			cout << argv[i];
		else
			cout << "(null)";

		if (i % 2 == 0)
			cout << ' ';
	}

	cout << "\n";
	return 0;
}

int Database::callback(void* data, int argc, char** argv, char** azColName) {

	for (int i = 0; i < argc; i++)
	{
		cout << azColName[i] << " = " << argv[i] ? argv[i] : "(null)";
		cout << '\n';
	}

	cout << '\n';
	return 0;
}

void Database::SignUp(){}
void Database::LogIn(){}

Database::Database(sqlite3* db, int type) : db(db), user_type(type) {}

void Database::loop(){}
void Database::Select4(){}
void Database::Select1(){}
void Database::Insert(){}
void Database::Update(){}
void Database::Delete(){}
void Database::Select5(){}
void Database::SelectAllOutRaces(){}
void Database::Select2(){}
void Database::prize_pool(){}
void Database::divide_prize(double){}
void Database::Select3(){}
void Database::Select6(){}

int Database::getUserType() const
{
	return user_type;
}

std::string Database::getSurname() const
{
	return surname;
}

Database::~Database() {}


void Database::clear()
{
	cout << "\033c";
}

void Database::def()
{
	cout << "Wrong input. Try again.\n";
}

void Database::terminate()
{
	throw 0;
}

void Database::SQL_Error(int rc, char* zErrMsg)
{
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}