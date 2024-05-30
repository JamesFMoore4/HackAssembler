#include "Table.h"

void initialize(Table* table)
{
	table->count = 0;
	table->capacity = INITIAL_TABLE_SIZE;
	table->symbols = (char**)malloc(table->capacity * sizeof(char*));
	table->addresses = (int*)malloc(table->capacity * sizeof(int));
	if (!table->symbols || !table->addresses)
	{
		fprintf(stderr, "Could not allocate memory for symbol table.");
		exit(1);
	}
	for (int i = 0; i < table->capacity; i++)
	{
		table->symbols[i] = (char*)malloc(MAX_SYMBOL_LENGTH * sizeof(char));
		if (!table->symbols[i])
		{
			fprintf(stderr, "Could not allocate memory for symbol table.");
			exit(1);
		}
	}
	predefSym(table);
}

void delete(Table* table)
{
	for (int i = 0; i < table->count; i++)
		free(table->symbols[i]);
	free(table->symbols);
	free(table->addresses);
}

void addEntry(Table* table, char* symbol, int address)
{
	if (strlen(symbol) + 1 > MAX_SYMBOL_LENGTH)
	{
		fprintf(stderr, "Symbol length too long");
		exit(1);
	}
	if (table->count == table->capacity)
		increaseSize(table);
	strcpy_s(table->symbols[table->count], MAX_SYMBOL_LENGTH, symbol);
	table->addresses[table->count++] = address;
}

bool contains(const Table* table, char* symbol)
{
	for (int i = 0; i < table->count; i++)
		if (!strcmp(table->symbols[i], symbol))
			return true;
	return false;
}

int getAddress(const Table* table, char* symbol)
{
	if (contains(table, symbol))
		for (int i = 0; i < table->count; i++)
			if (!strcmp(table->symbols[i], symbol))
				return table->addresses[i];
	fprintf(stderr, "Symbol not found.");
	exit(1);
}

static void increaseSize(Table* table)
{
	table->capacity *= 2;
	char** tempSymbols = table->symbols;
	int* tempAddresses = table->addresses;

	table->symbols = (char**)malloc(table->capacity * sizeof(char*));
	table->addresses = (int*)malloc(table->capacity * sizeof(int));
	if (table->symbols && table->addresses)
		for (int i = 0; i < table->capacity; i++)
			table->symbols[i] = (char*)malloc(MAX_SYMBOL_LENGTH * sizeof(char));
	else
	{
		fprintf(stderr, "Could not increase size of symbol table.");
		exit(1);
	}
		
	for (int i = 0; i < table->count; i++)
	{
		if (*(table->symbols + i))
		{
			strcpy_s(*(table->symbols + i), MAX_SYMBOL_LENGTH, tempSymbols[i]);
			*(table->addresses + i) = tempAddresses[i];
		}
		else
		{
			fprintf(stderr, "Could not increase size of symbol table.");
			exit(1);
		}
	}
	
	free(tempSymbols);
	free(tempAddresses);
}

static void predefSym(Table* table)
{
	char r[3] = "RX";
	for (int i = 0; i < 10; i++)
	{
		r[1] = i + 48;
		addEntry(table, r, i);
	}
	addEntry(table, "R10", 10);
	addEntry(table, "R11", 11);
	addEntry(table, "R12", 12);
	addEntry(table, "R13", 13);
	addEntry(table, "R14", 14);
	addEntry(table, "R15", 15);
	addEntry(table, "SP", 0);
	addEntry(table, "LCL", 1);
	addEntry(table, "ARG", 2);
	addEntry(table, "THIS", 3);
	addEntry(table, "THAT", 4);
}