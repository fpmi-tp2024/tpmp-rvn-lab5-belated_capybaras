#define _CRT_SECURE_NO_WARNINGS

#include "../inc/owner.h"
#include "../inc/clear.h"

void owner_loop(sqlite3* db, const char* surname)
{
	while (1)
	{
		printf("Owner Action:\n");
		printf("1. Read\n");
		printf("2. Exit\n");
		int choice = 10;
		char c = '0';
		if (scanf("%d", &choice) == 0)
		{
			printf("Wrong input. Try again.\n");
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}

		void (*functions[]) (void*, void*) = { owner_read_loop, terminate2 };
		if (choice >= 1 && choice <= 2 && functions[choice - 1])
		{
			functions[choice - 1](db, surname);
		}
		else
		{
			def(NULL);
		}
	}


}

void owner_read_loop(sqlite3* db, const char* surname)
{
	while (1)
	{
		printf("Read:\n");
		printf("1. My Horses and Races\n");
		printf("2. My Best Horse\n");
		printf("3. Exit\n");
		int choice = 10;
		char c = '0';
		if (scanf("%d", &choice) == 0)
		{
			printf("Wrong input. Try again.\n");
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}

		void (*functions[]) (void*, void*) = { Select4, Select1, terminate2 };
		if (choice >= 1 && choice <= 3 && functions[choice - 1])
		{
			functions[choice - 1](db, surname);
		}
		else
		{
			def(NULL);
		}
	}
}