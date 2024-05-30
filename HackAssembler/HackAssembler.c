#include <ctype.h>

#include "Table.h"
#include "Parser.h"
#include "Code.h"

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

	/*for (int i = 0; i < symTable.count; i++)
		printf("Symbol: %s, Address: %d\n", symTable.symbols[i], symTable.addresses[i]);*/

	delete(&symTable);
	fclose(input);

	return 0;
}

void firstPass(FILE* input, Table* symTable)
{
	int lineNum = -1;
	while (hasMoreLines(input))
	{
		char line[MAX_LINE_LENGTH];
		char asm[MAX_LINE_LENGTH];
		char sym[MAX_SYMBOL_LENGTH];

		fgets(line, MAX_LINE_LENGTH, input);
		trim(line, asm);
		
		Type instrType = instructionType(asm);
		if (instrType == A_INSTRUCTION || instrType == C_INSTRUCTION)
			lineNum++;
		else if (instrType == L_INSTRUCTION)
		{
			symbol(asm, sym);
			addEntry(symTable, sym, lineNum + 1);
		}
	}
}

void secondPass(FILE* input, const Table* symTable, char* inpath)
{
	char outpath[MAX_LINE_LENGTH];
	strcpy_s(outpath, strlen(inpath) + 1, inpath);
	strcpy_s(outpath + strlen(outpath) - 3, 5, "hack");

	FILE* output = fopen(outpath, "wt");
	if (!output)
	{
		fprintf(stderr, "Could not open output file for writing.");
		exit(1);
	}

	while (1)
	{
		int ramaddr = 16;

		char line[MAX_LINE_LENGTH];
		char asm[MAX_LINE_LENGTH];

		fgets(line, MAX_LINE_LENGTH, input);
		if (!hasMoreLines(input))
			break;

		trim(line, asm);

		Type instrType = instructionType(asm);
		if (instrType == A_INSTRUCTION)
		{
			char sym[MAX_SYMBOL_LENGTH];
			char binAddr[16];
			symbol(asm, sym);
			if (isdigit(sym[0]))
			{
				itob(binAddr, atoi(sym));
			}
			else
			{
				if (contains(symTable, sym))
				{
					itob(binAddr, getAddress(symTable, sym));
				}
				else
				{
					addEntry(symTable, sym, ramaddr++);
					itob(binAddr, getAddress(symTable, sym));
				}
			}
			fprintf(output, "0%s\n", binAddr);
		}
		else if (instrType == C_INSTRUCTION)
		{
			char compinstr[8], destinstr[8], jumpinstr[8];
			char compbin[12], destbin[8], jumpbin[8];
			compP(asm, compinstr);
			destP(asm, destinstr);
			jumpP(asm, jumpinstr);
			comp(compinstr, compbin);
			dest(destinstr, destbin);
			jump(jumpinstr, jumpbin);
			fprintf(output, "111%s%s%s\n", compbin, destbin, jumpbin);
		}
	}

	fclose(output);
}
