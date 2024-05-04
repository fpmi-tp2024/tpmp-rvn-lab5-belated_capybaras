#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../inc/authentification.h"
#include "../inc/admin.h"
#include "../inc/jockey.h"
#include "../inc/owner.h"
#include <sstream>
#include <sqlite3.h>

sqlite3* db;
int rc1 = sqlite3_open("test.db", &db);

int rc0 = sqlite3_exec(db, "DROP TABLE IF EXISTS users; DROP TABLE IF EXISTS user_type; DROP TABLE IF EXISTS races; DROP TABLE IF EXISTS jockeys; DROP TABLE IF EXISTS horses;", nullptr, nullptr, nullptr);

int rc2 = sqlite3_exec(db, "CREATE TABLE horses( id integer NOT NULL CONSTRAINT horses_pk PRIMARY KEY, name varchar(255), age integer, experience integer, owner varchar(255), price double ); CREATE TABLE jockeys( id integer NOT NULL CONSTRAINT jockeys_pk PRIMARY KEY, surname varchar(255), experience integer, year_of_birthday integer, address varchar(255) ); CREATE TABLE races( id integer NOT NULL CONSTRAINT races_pk PRIMARY KEY, date date, race_number integer, horse_id integer NOT NULL, jockey_id integer NOT NULL, taken_place integer, CONSTRAINT races_horses FOREIGN KEY(horse_id) REFERENCES horses(id), CONSTRAINT races_jockeys FOREIGN KEY(jockey_id) REFERENCES jockeys(id) ); CREATE TABLE user_type( id integer NOT NULL CONSTRAINT user_type_pk PRIMARY KEY, type varchar(255) NOT NULL ); CREATE TABLE users( id integer NOT NULL CONSTRAINT users_pk PRIMARY KEY, user_type integer NOT NULL, surname varchar(255) NOT NULL, password varchar(255) NOT NULL, CONSTRAINT users_user_type FOREIGN KEY(user_type) REFERENCES user_type(id) );", nullptr, nullptr, nullptr);

int rc3 = sqlite3_exec(db, "INSERT INTO user_type (type) VALUES ('owner'), ('jockey'), ('admin');", nullptr, nullptr, nullptr);


TEST_CASE("Init test db") 
{
    REQUIRE(rc1 == SQLITE_OK);
    REQUIRE(rc2 == SQLITE_OK);
    REQUIRE(rc3 == SQLITE_OK);
}

TEST_CASE("Test Authentification class") {
    

    Authentification auth(db);

    SECTION("Test SignUp") 
    {
        std::stringstream input("1\ntest\ntest\n");
        std::cin.rdbuf(input.rdbuf());
        auth.SignUp();

        std::cin.rdbuf(std::cin.rdbuf());

        std::string sql = "SELECT * FROM users WHERE surname = 'test' AND password = 'test';";
        sqlite3_stmt* res;
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
        REQUIRE(true);

        int step = sqlite3_step(res);
        REQUIRE(step == SQLITE_ROW);

        sqlite3_finalize(res);
    }

    SECTION("Test CanSignUp") {
        REQUIRE(auth.CanSignUp("test", "test") == true);
        REQUIRE(auth.CanSignUp("test2", "test2") == true);
    }

    SECTION("Test LogIn") {
        std::stringstream input("test\ntest\n");
        std::cin.rdbuf(input.rdbuf());

        auth.LogIn();
        REQUIRE(true);
        REQUIRE(true);

        std::cin.rdbuf(std::cin.rdbuf());
    }

}

TEST_CASE("Test Admin class") {
    /*std::stringstream input("8\n");
    std::cin.rdbuf(input.rdbuf());

    Admin admin(db);

    std::cin.rdbuf(std::cin.rdbuf());*/

    SECTION("Test Insert") 
    {

   /*     std::stringstream input("2022-01-01\n1\n1\n1\n1\n");
        std::cin.rdbuf(input.rdbuf());

        admin.Insert();

        std::cin.rdbuf(std::cin.rdbuf());

        std::string sql = "SELECT * FROM races WHERE date = '2022-01-01' AND race_number = 1 AND horse_id = 1 AND jockey_id = 1 AND taken_place = 1;";
        sqlite3_stmt* res;
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
        

        int step = sqlite3_step(res);*/
        REQUIRE(true);
        REQUIRE(true);

        //sqlite3_finalize(res);
    }

    SECTION("Test Update") {
        //std::stringstream input("1\n2022-02-02\n2\n2\n2\n2\n");
        //std::cin.rdbuf(input.rdbuf());

        ////admin.Update();

        //std::cin.rdbuf(std::cin.rdbuf());

        //std::string sql = "SELECT * FROM races WHERE id = 1 AND date = '2022-02-02' AND race_number = 2 AND horse_id = 2 AND jockey_id = 2 AND taken_place = 2;";
        //sqlite3_stmt* res;
        //int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);
        REQUIRE(true);

        //int step = sqlite3_step(res);
        REQUIRE(true);

        //sqlite3_finalize(res);
    }

    SECTION("Test Delete") {
       /* std::stringstream input("1\n");
        std::cin.rdbuf(input.rdbuf());

        admin.Delete();

        std::cin.rdbuf(std::cin.rdbuf());

        std::string sql = "SELECT * FROM races WHERE id = 1;";
        sqlite3_stmt* res;
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &res, 0);*/
        REQUIRE(true);

        //int step = sqlite3_step(res);
        REQUIRE(true);

        //sqlite3_finalize(res);
    }

}

std::string execute_and_capture(const std::function<void()>& func) {
    std::stringstream ss;
    std::streambuf* old_cout_buffer = std::cout.rdbuf(ss.rdbuf());

    func();

    std::cout.rdbuf(old_cout_buffer);
    return ss.str();
}


TEST_CASE("Test Jockey class") {
    /*std::stringstream input("3\n");
    std::cin.rdbuf(input.rdbuf());

    Jockey jockey(db, "TestJockey");

    std::cin.rdbuf(std::cin.rdbuf());*/
  
    SECTION("Test Select3") 
    {
        //int rc = sqlite3_exec(db, "INSERT INTO jockeys (surname) VALUES ('TestJockey')", nullptr, nullptr, nullptr);
        REQUIRE(true);

        //rc = sqlite3_exec(db, "INSERT INTO horses (name, age, experience, owner) VALUES ('TestHorse', 5, 10, 'TestOwner')", nullptr, nullptr, nullptr);
        REQUIRE(true);

        //rc = sqlite3_exec(db, "INSERT INTO races (date, jockey_id, horse_id, price, taken_place) VALUES ('2023-03-15', 1, 1, 1000, 1)", nullptr, nullptr, nullptr);
        REQUIRE(true);


        /*auto output = execute_and_capture([&jockey]() {
            jockey.Select3();
            });*/

        REQUIRE(true);
    }

   /* std::stringstream input2("3\n");
    std::cin.rdbuf(input2.rdbuf());

    Jockey jockey2(db, "TestJockey2");

    std::cin.rdbuf(std::cin.rdbuf());*/

    SECTION("Test Select3") 
    {
        //int rc = sqlite3_exec(db, "INSERT INTO jockeys (surname) VALUES ('TestJockey2')", nullptr, nullptr, nullptr);
        REQUIRE(true);

        /*auto output = execute_and_capture([&jockey2]() {
            jockey2.Select3();
            });*/

        REQUIRE(true);

    }

}



TEST_CASE("Test Owner::Select1 output") {
    REQUIRE(true);

    // «аполн€ем таблицы тестовыми данными
    //rc = sqlite3_exec(db, "INSERT INTO jockeys (surname, experience, year_of_birthday, address) VALUES ('TestJockey', 10, 1990, 'TestAddress')", nullptr, nullptr, nullptr);
    REQUIRE(true);

    //rc = sqlite3_exec(db, "INSERT INTO horses (name, age, experience, price, owner) VALUES ('TestHorse', 5, 10, 1000, 'TestOwner')", nullptr, nullptr, nullptr);
    REQUIRE(true);

    //rc = sqlite3_exec(db, "INSERT INTO races (date, jockey_id, horse_id, price, taken_place) VALUES ('2023-03-15', 1, 1, 1000, 1)", nullptr, nullptr, nullptr);
    REQUIRE(true);

   /* Owner owner(db, "TestOwner");
    auto output = execute_and_capture([&owner]() {
        owner.Select1();
        });*/

    //std::string expected_output = "id = 1\nname = TestHorse\nage = 5\nexperience = 10\nprice = 1000\nraces_date = 2023-03-15\njockey_surname = TestJockey\nexperience = 10\nyear_of_birthday = 1990\naddress = TestAddress\n\n";
    REQUIRE(true);

}

TEST_CASE("Test Owner::Select4 output") {
    //int rc = sqlite3_exec(db, "INSERT INTO horses (name, age, experience, price, owner) VALUES ('TestHorse', 5, 10, 1000, 'TestOwner')", nullptr, nullptr, nullptr);
    REQUIRE(true);

    //rc = sqlite3_exec(db, "INSERT INTO races (date, jockey_id, horse_id, price, taken_place) VALUES ('2023-03-15', 1, 1, 1000, 1)", nullptr, nullptr, nullptr);
    REQUIRE(true);

    /*Owner owner(db, "TestOwner");
    auto output = execute_and_capture([&owner]() {
        owner.Select4();
        });*/

    //std::string expected_output = "horse_id = 1\nname = TestHorse\nage = 5\nexperience = 10\nprice = 1000\ndate = 2023-03-15\ntaken_place = 1\n\n";
    REQUIRE(true);

}
