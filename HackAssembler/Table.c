#include "Table.h"
#define INITIAL_TABLE_SIZE 32
#define MAX_STRING_LENGTH 64

void initialize(Table* table)
{
	table->count = 0;
	table->capacity = INITIAL_TABLE_SIZE;
	table->symbols = (char**)malloc(INITIAL_TABLE_SIZE * sizeof(char*));
	table->addresses = (int*)malloc(INITIAL_TABLE_SIZE * sizeof(int));

	if (table->symbols)
	{
		for (int i = 0; i < INITIAL_TABLE_SIZE; i++)
			*(table->symbols + i) = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
	}
	else
	{
		fprintf(stderr, "Could not allocate memory for symbol table.");
		exit(1);
	}
}

void delete(Table* table)
{
	for (int i = 0; i < table->count; i++)
		free(*(table->symbols + i));
	free(table->symbols);
	free(table->addresses);
}

void addEntry(Table* table, char* symbol, int address)
{
	if (sizeof(symbol) > MAX_STRING_LENGTH)
	{
		fprintf(stderr, "Symbol length too long");
		exit(1);
	}

	if (table->count == table->capacity)
		increaseSize(table);

	strcpy_s(*(table->symbols + table->count), MAX_STRING_LENGTH, symbol);
	*(table->addresses + table->count++) = address;
}

bool contains(const Table* table, char* symbol)
{
	for (int i = 0; i < table->count; i++)
		if (!strcmp(*(table->symbols + i), symbol))
			return true;
	return false;
}

int getAddress(const Table* table, char* symbol)
{

	if (contains(table, symbol))
	{
		int i;
		for (i = 0; i < table->count; i++)
			if (!strcmp(*(table->symbols + i), symbol))
				break;
		return *(table->addresses + i);
	}
	else
	{
		fprintf(stderr, "Symbol not found.");
		exit(1);
	}
}

static void increaseSize(Table* table)
{
	table->capacity <<= 1;

	char** tempSymbols = table->symbols;
	int* tempAddresses = table->addresses;

	table->symbols = (char**)malloc(table->capacity * sizeof(char*));
	table->addresses = (int*)malloc(table->capacity * sizeof(int));
	if (table->symbols && table->addresses)
	{
		for (int i = 0; i < table->capacity; i++)
			*(table->symbols + i) = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
	}
	else
		goto Error;

	
	for (int i = 0; i < table->count; i++)
	{
		if (*(table->symbols + i))
			strcpy_s(*(table->symbols + i), MAX_STRING_LENGTH, *(tempSymbols + i));
		else
			goto Error;
		*(table->addresses + i) = *(tempAddresses + i);
	}

	return;

	Error:
		fprintf(stderr, "Could not increase size of table.");
		exit(1);
}
