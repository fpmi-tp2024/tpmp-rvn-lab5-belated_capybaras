#define _CRT_SECURE_NO_WARNINGS

#include "../inc/jockey.h"
#include "../inc/clear.h"


void jockey_loop(sqlite3* db, const char* surname)
{
	while (1)
	{
		printf("Jockey Action:\n");
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

		if (choice == 1)
		{
			jockey_read_loop(db, surname);
		}
		else if (choice == 2)
		{
			terminate(NULL);
		}
		else 
		{
			def(NULL);
		}
	}


}

void jockey_read_loop(sqlite3* db, const char* surname)
{
	while (1)
	{
		printf("Read:\n");
		printf("1. My Races\n");
		printf("2. Select My Races\n");
		printf("3. Exit\n");
		int choice = 10;
		char c = '0';
		if (scanf("%d", &choice) == 0)
		{
			printf("Wrong input. Try again.\n");
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}

		void (*functions[]) (void*, void*) = { Select3, Select6, terminate2 };
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