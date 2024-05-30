#include <ctype.h>

#include "Table.h"
#include "Parser.h"
#include "Code.h"

int ramaddr = 16;

void firstPass(FILE* input, Table* symTable);
void secondPass(FILE* input, const Table* symTable, char* in);

int main(int argc, char* argv[])
{
	if (argc != 2 || !isValidPath(argv[1]))
	{
		puts("Usage: HackAssembler *.asm");
		return 0;
	}

	FILE* input = fopen(argv[1], "rt");
	if (!input)
	{
		fprintf(stderr, "Input file could not be opened for reading.");
		return 1;
	}

	Table symTable;
	initialize(&symTable);

	firstPass(input, &symTable);
	rewind(input);
	secondPass(input, &symTable, argv[1]);

	delete(&symTable);
	fclose(input);

	return 0;
}

void firstPass(FILE* input, Table* symTable)
{
	
}

void secondPass(FILE* input, const Table* symTable, char* in)
{
	
}
