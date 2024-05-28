#include "Table.h"
#include "Parser.h"
#include "Code.h"

#define MAX_INSTR_LENGTH 256

bool isValidPath(char* path);
void firstPass(FILE* input, Table* symTable);
void secondPass(FILE* input, const Table* symTable);
void trim(const char* instr, char* buffer);

int main(int argc, char* argv[])
{
	if (argc != 2 || !isValidPath(argv[1]))
	{
		puts("Usage: HackAssembler *.asm");
		return 1;
	}

	FILE* input = fopen(argv[1], "rt");
	if (!input)
	{
		puts("Input file could not be opened for reading.");
		return 1;
	}

	Table symTable;
	initialize(&symTable);

	firstPass(input, &symTable);
	rewind(input);
	secondPass(input, &symTable);

	delete(&symTable);
	fclose(input);
	return 0;
}

bool isValidPath(char* path)
{
	int pathlen = (int)strlen(path);
	if (pathlen < 5)
		return false;

	char* extension = path + pathlen - 4;
	if (strcmp(extension, ".asm"))
		return false;

	return true;
}

void firstPass(FILE* input, Table* symTable)
{
	char instrbuffer[MAX_INSTR_LENGTH];
	char trimmedinstr[MAX_INSTR_LENGTH];
	char symbolinstr[MAX_STRING_LENGTH];
	char destinstr[2];
	char compinstr[4];
	char jump[4];
	int linecntr = 0, ramaddr = 16;

	while (hasMoreLines(input))
	{
		fgets(instrbuffer, MAX_INSTR_LENGTH, input);
		trim(instrbuffer, trimmedinstr);
		Type instrtype = instructionType(trimmedinstr);
		
		if (instrtype == A_INSTRUCTION || instrtype == L_INSTRUCTION)
		{
			symbol(trimmedinstr, symbolinstr);
			if (!contains(symTable, symbolinstr))
			{
				instrtype ? addEntry(symTable, symbolinstr, ramaddr++) : addEntry(symTable, symbolinstr, linecntr + 1);
			}
		}
		else if (instrtype == NOT_INSTRUCTION)
			continue;
		linecntr++;
	}
}

void secondPass(FILE* input, const Table* symTable)
{

}

void trim(const char* instr, char* buffer)
{
	char temp[MAX_INSTR_LENGTH];
	int i, pos;
	for (i = 0, pos = 0; instr[i]; i++)
	{
		if (instr[i] == '/' && instr[i + 1] == '/')
			break;
		if (instr[i] == ' ')
			continue;
		temp[pos++] = instr[i];
	}
	temp[pos] = '\0';
	strcpy_s(buffer, sizeof(temp), temp);
}