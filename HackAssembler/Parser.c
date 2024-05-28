#include "Parser.h"

bool hasMoreLines(FILE* input)
{
	return !feof(input);
}

Type instructionType(const char* instr)
{
	if (instr[0] == '@')
		return A_INSTRUCTION;
	else if (instr[0] == '(')
		return L_INSTRUCTION;
	return C_INSTRUCTION;
}

void symbol(const char* instr, char* buffer)
{
	char temp[64];
	Type instrtype = instructionType(instr);
	if (instrtype == L_INSTRUCTION)
	{
		int i = 0;
		char temp[64];
		while (instr[i + 1] != ')')
		{
			temp[i] = instr[i + 1];
			i++;
		}
		temp[i] = '\0';
		strcpy_s(buffer, 64, temp);
	}
	else
		strcpy_s(buffer, 64, instr + 1);
}

void destP(const char* instr, char* buffer)
{
	bool present = containsP(instr, '=');
	if (present)
	{
		char dest[] = " ";
		dest[0] = instr[0];
		strcpy_s(buffer, 2, dest);
	}
	else
		strcpy_s(buffer, 2, "");
}

void compP(const char* instr, char* buffer)
{
	bool presentE = containsP(instr, '=');
	bool presentS = containsP(instr, ';');
	
	int i;
	char temp[4];
	int count = 0;
	temp[3] = '\0';
	if (presentE && presentS)
	{
		i = 2;
		while (instr[i] != ';')
		{
			temp[i++ - 2] = instr[i];
			count++;
		}
	}
	else if (presentS)
	{
		i = 0;
		while (instr[i] != ';')
		{
			temp[i++] = instr[i];
			count++;
		}
	}
	else
	{
		i = 2;
		while (instr[i] != '\0')
		{
			temp[i++ - 2] = instr[i];
			count++;
		}
	}
	temp[count] = '\0';
	strcpy_s(buffer, 4, temp);
}

void jumpP(const char* instr, char* buffer)
{
	bool present = containsP(instr, ';');

	if (present)
	{
		char *ptr = strchr(instr, ';'), temp[4];
		ptr++;
		temp[3] = '\0';
		int i = 0;
		while (*ptr)
			temp[i++] = *(ptr++);
		strcpy_s(buffer, 4, temp);
	}
	else
		strcpy_s(buffer, 2, "");
}

static bool containsP(const char* str, char c)
{
	bool present = false;
	for (char* ptr = str; *ptr != '\0'; ptr++)
		if (*ptr == c)
			present = true;
	return present;
}