#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
	int capacity;
	int count;
	char** symbols;
	int* addresses;
} Table;

void initialize(Table* table);

void delete(Table* table);

void addEntry(Table* table, char* symbol, int address);

bool contains(const Table* table, char* symbol);

int getAddress(const Table* table, char* symbol);

static void increaseSize(Table* table);


