#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../inc/authentification.h"
#include "../inc/admin.h"
#include "../inc/jockey.h"

#include <sstream>
#include <sqlite3.h>


TEST_CASE("Test Authentification class") {
    sqlite3* db;
    int rc = sqlite3_open("test.db", &db);
    REQUIRE(rc == SQLITE_OK);

    Authentification auth(db);

    SECTION("Test SignUp") 
    {
        std::stringstream input("1\ntest\ntest\n");
        std::cin.rdbuf(input.rdbuf());
        auth.SignUp();

        std::cin.rdbuf(std::cin.rdbuf());

        std::string sql = "SELECT * FROM users WHERE surname = 'test' AND password = 'test';";
        sqlite3_stmt* res;
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
        REQUIRE(rc == SQLITE_OK);

        int step = sqlite3_step(res);
        REQUIRE(step == SQLITE_ROW);

        sqlite3_finalize(res);
    }

    SECTION("Test CanSignUp") {
        REQUIRE(auth.CanSignUp("test", "test") == false);
        REQUIRE(auth.CanSignUp("test2", "test2") == true);
    }

    SECTION("Test LogIn") {
        std::stringstream input("test\ntest\n");
        std::cin.rdbuf(input.rdbuf());

        auth.LogIn();
        REQUIRE(auth.getUserType() == 1);
        REQUIRE(auth.getSurname() == "test");

        std::cin.rdbuf(std::cin.rdbuf());
    }

    sqlite3_close(db);
}

TEST_CASE("Test Admin class") {
    sqlite3* db;
    int rc = sqlite3_open("test.db", &db);
    REQUIRE(rc == SQLITE_OK);

    Admin admin(db);

    SECTION("Test Insert") {
        std::stringstream input("2022-01-01\n1\n1\n1\n1\n");
        std::cin.rdbuf(input.rdbuf());

        admin.Insert();

        std::cin.rdbuf(std::cin.rdbuf());

        std::string sql = "SELECT * FROM races WHERE date = '2022-01-01' AND race_number = 1 AND horse_id = 1 AND jockey_id = 1 AND taken_place = 1;";
        sqlite3_stmt* res;
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
        REQUIRE(rc == SQLITE_OK);

        int step = sqlite3_step(res);
        REQUIRE(step == SQLITE_ROW);

        sqlite3_finalize(res);
    }

    SECTION("Test Update") {
        std::stringstream input("1\n2022-02-02\n2\n2\n2\n2\n");
        std::cin.rdbuf(input.rdbuf());

        admin.Update();

        std::cin.rdbuf(std::cin.rdbuf());

        std::string sql = "SELECT * FROM races WHERE id = 1 AND date = '2022-02-02' AND race_number = 2 AND horse_id = 2 AND jockey_id = 2 AND taken_place = 2;";
        sqlite3_stmt* res;
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
        REQUIRE(rc == SQLITE_OK);

        int step = sqlite3_step(res);
        REQUIRE(step == SQLITE_ROW);

        sqlite3_finalize(res);
    }

    SECTION("Test Delete") {
        std::stringstream input("1\n");
        std::cin.rdbuf(input.rdbuf());

        admin.Delete();

        std::cin.rdbuf(std::cin.rdbuf());

        std::string sql = "SELECT * FROM races WHERE id = 1;";
        sqlite3_stmt* res;
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
        REQUIRE(rc == SQLITE_OK);

        int step = sqlite3_step(res);
        REQUIRE(step == SQLITE_DONE);

        sqlite3_finalize(res);
    }

    sqlite3_close(db);
}

std::string execute_and_capture(const std::function<void()>& func) {
    std::stringstream ss;
    std::streambuf* old_cout_buffer = std::cout.rdbuf(ss.rdbuf());

    func();

    std::cout.rdbuf(old_cout_buffer);
    return ss.str();
}


TEST_CASE("Test Jockey class") {
    sqlite3* db;
    int rc = sqlite3_open("test.db", &db);
    REQUIRE(rc == SQLITE_OK);

    std::stringstream input("1\n");
    std::cin.rdbuf(input.rdbuf());

    Jockey jockey(db, "TestJockey");

    std::cin.rdbuf(std::cin.rdbuf());

    rc = sqlite3_exec(db, "CREATE TABLE jockeys (id INTEGER PRIMARY KEY, surname TEXT)", nullptr, nullptr, nullptr);
    REQUIRE(rc == SQLITE_OK);

    rc = sqlite3_exec(db, "CREATE TABLE horses (id INTEGER PRIMARY KEY, name TEXT, age INTEGER, experience INTEGER, owner TEXT)", nullptr, nullptr, nullptr);
    REQUIRE(rc == SQLITE_OK);

    rc = sqlite3_exec(db, "CREATE TABLE races (id INTEGER PRIMARY KEY, date TEXT, jockey_id INTEGER, horse_id INTEGER, price INTEGER, taken_place INTEGER)", nullptr, nullptr, nullptr);
    REQUIRE(rc == SQLITE_OK);
  

    SECTION("Test Select3") 
    {
        rc = sqlite3_exec(db, "INSERT INTO jockeys (surname) VALUES ('TestJockey')", nullptr, nullptr, nullptr);
        REQUIRE(rc == SQLITE_OK);

        rc = sqlite3_exec(db, "INSERT INTO horses (name, age, experience, owner) VALUES ('TestHorse', 5, 10, 'TestOwner')", nullptr, nullptr, nullptr);
        REQUIRE(rc == SQLITE_OK);

        rc = sqlite3_exec(db, "INSERT INTO races (date, jockey_id, horse_id, price, taken_place) VALUES ('2023-03-15', 1, 1, 1000, 1)", nullptr, nullptr, nullptr);
        REQUIRE(rc == SQLITE_OK);


        auto output = execute_and_capture([&jockey]() {
            jockey.Select3();
            });

        REQUIRE(output == "date = 2023-03-15\nhorse_id = 1\nname = TestHorse\nage = 5\nexperience = 10\nowner = TestOwner\nprice = 1000\ntaken_place = 1\n\n");

        sqlite3_close(db);
    }

    std::stringstream input2("1\n");
    std::cin.rdbuf(input2.rdbuf());

    Jockey jockey2(db, "TestJockey2");

    std::cin.rdbuf(std::cin.rdbuf());

    SECTION("Test Select3") 
    {
        rc = sqlite3_exec(db, "INSERT INTO jockeys (surname) VALUES ('TestJockey2')", nullptr, nullptr, nullptr);
        REQUIRE(rc == SQLITE_OK);

        auto output = execute_and_capture([&jockey2]() {
            jockey2.Select3();
            });

        REQUIRE(output == "This jockey did not participate in the races\n");

        sqlite3_close(db);
    }

    sqlite3_close(db);
}

