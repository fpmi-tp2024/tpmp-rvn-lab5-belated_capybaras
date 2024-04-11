#include "../inc/clear.h"
#include "../inc/hippodrome.h"
#include <stdio.h>

void clear(void* db)
{
	printf("\033c");
}

void def(void* db)
{
	printf("Wrong input. Try again.\n");
}

void terminate(void* db)
{
	exit(0);
}

void terminate2(void* db1, void* db2)
{
	exit(0);
}

void prize_pool(void* db)
{
	double* prize = (double*)db;
	printf("Input prize pool: ");
	if (scanf("%lf", prize) == 0)
	{
		printf("Wrong input. Try again.\n");
		char c;
		while ((c = getchar()) != '\n' && c != EOF);
		return;
	}

	divide_prize(*prize);
	printf("\n\n");
}

