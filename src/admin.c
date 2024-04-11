#define _CRT_SECURE_NO_WARNINGS

#include "../inc/admin.h"
#include "../inc/clear.h"

void admin_loop(sqlite3* db)
{
	while (1)
	{
		printf("Admin Action:\n");
		printf("1. Insert Race\n");
		printf("2. Update Race\n");
		printf("3. Delete Race\n");
		printf("4. Output Races\n");
		printf("5. Misc\n");
		printf("6. Exit\n");
		printf("7. Clear\n");
		int choice = 10;
		char c = '0';
		if (scanf("%d", &choice) == 0)
		{
			printf("Wrong input. Try again.\n");
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}

		void (*functions[]) (void*) = { Insert, Update, Delete, Select5, admin_misc_loop, terminate, clear};
		if (choice >= 1 && choice <= 7 && functions[choice - 1])
		{
			functions[choice - 1](db);
		}
		else
		{
			def(NULL);
		}
	}


}


void admin_misc_loop(sqlite3* db)
{
	while (1)
	{
		printf("Select:\n");
		printf("1. Best Horse\n");
		printf("2. Best Jockey\n");
		printf("3. Divide prize pool\n");
		printf("4. Exit\n");
		printf("5. Clear\n");

		double prize = 0;
		int choice = 10;
		char c = '0';
		if (scanf("%d", &choice) == 0)
		{
			printf("Wrong input. Try again.\n");
			while ((c = getchar()) != '\n' && c != EOF);
			continue;
		}

		void (*functions[]) (void*) = { Select1, Select2, prize_pool, terminate, clear };
		if (choice >= 1 && choice <= 5 && functions[choice - 1])
		{
			functions[choice - 1](db);
		}
		else
		{
			def(NULL);
		}
	}
}