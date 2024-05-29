#include <ctype.h>

#include "Table.h"
#include "Parser.h"
#include "Code.h"

#define MAX_INSTR_LENGTH 256

int ramaddr = 16;

bool isValidPath(char* path);
void firstPass(FILE* input, Table* symTable);
void secondPass(FILE* input, const Table* symTable, char* in);
void trim(const char* instr, char* buffer);

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
	/*for (int i = 0; i < symTable.count; i++)
		printf("Symbol: %s, Address: %d\n", symTable.symbols[i], symTable.addresses[i]);*/
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
	char instrbuffer[MAX_INSTR_LENGTH], trimmedinstr[MAX_INSTR_LENGTH], symbolinstr[MAX_STRING_LENGTH];
	int linecntr = 0;
	while (hasMoreLines(input))
	{
		fgets(instrbuffer, MAX_INSTR_LENGTH, input);
		trim(instrbuffer, trimmedinstr);
		Type instrtype = instructionType(trimmedinstr);
		
		if (instrtype == L_INSTRUCTION)
		{
			symbol(trimmedinstr, symbolinstr);
			if (!contains(symTable, symbolinstr))
				addEntry(symTable, symbolinstr, linecntr + 1);
		}
		else if (instrtype == NOT_INSTRUCTION)
			continue;
		linecntr++;
	}
}

void secondPass(FILE* input, const Table* symTable, char* in)
{
	// Change file extension
	int pathlen = strlen(in);
	char* extension = in + pathlen - 3;
	strcpy_s(extension, 5, "hack");

	FILE* output = fopen(in, "wt");
	if (!output)
	{
		fprintf(stderr, "Could not open output file for writing.");
		exit(1);
	}

	while (hasMoreLines(input))
	{
		char instrbuffer[MAX_INSTR_LENGTH], trimmedinstr[MAX_INSTR_LENGTH];
		fgets(instrbuffer, MAX_INSTR_LENGTH, input);
		trim(instrbuffer, trimmedinstr);
		Type instrtype = instructionType(trimmedinstr);
		if (instrtype == A_INSTRUCTION)
		{
			char binary[17], instrout[18] = "0", symbolinstr[MAX_STRING_LENGTH];
			symbol(trimmedinstr, symbolinstr);
			if (isdigit(symbolinstr[0]))
			{
				itob(binary, atoi(symbolinstr));
			}
			else if (contains(symTable, symbolinstr))
			{
				itob(binary, getAddress(symTable, symbolinstr));
			}
			else
			{
				addEntry(symTable, symbolinstr, ramaddr++);
				itob(binary, getAddress(symTable, symbolinstr));
			}
			strcat_s(instrout, sizeof(binary), binary);
			printf("%s\n", instrout);
			fputs(instrout, output);
		}
		else if(instrtype == C_INSTRUCTION)
		{
			char destinstr[MAX_STRING_LENGTH], compinstr[MAX_STRING_LENGTH], jumpinstr[MAX_STRING_LENGTH];
			char instrout[18] = "111", compbin[9], destbin[5], jumpbin[5];
			destP(trimmedinstr, destinstr);
			dest(destinstr, destbin);
			compP(trimmedinstr, compinstr);
			dest(compinstr, compbin);
			jumpP(trimmedinstr, jumpinstr);
			jump(jumpinstr, jumpbin);
			strcat_s(instrout, sizeof(compbin), compbin);
			strcat_s(instrout, sizeof(destbin), destbin);
			strcat_s(instrout, sizeof(jumpbin), jumpbin);
			fputs(instrout, output);
		}
	}
	fclose(output);
}

void trim(const char* instr, char* buffer)
{
	char temp[MAX_INSTR_LENGTH];
	int i, pos;
	for (i = 0, pos = 0; instr[i]; i++)
	{
		if (instr[i] == '/' && instr[i + 1] == '/')
			break;
		if (instr[i] == ' ' || instr[i] == '\t')
			continue;
		temp[pos++] = instr[i];
	}
	temp[pos] = '\0';
	strcpy_s(buffer, sizeof(temp), temp);
}