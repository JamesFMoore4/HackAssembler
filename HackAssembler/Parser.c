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
	else if (!strcmp(instr, ""))
		return NOT_INSTRUCTION;
	return C_INSTRUCTION;
}

void symbol(const char* instr, char* buffer)
{
	if (instructionType(instr) == L_INSTRUCTION)
	{
		char temp[MAX_STRING_LENGTH];
		int i, pos;
		for (i = 0, pos = 0; instr[i]; i++)
			if (instr[i] != '(' && instr[i] != ')')
				temp[pos++] = instr[i];
		temp[pos] = '\0';
		strcpy_s(buffer, MAX_STRING_LENGTH, temp);
	}
	else
		strcpy_s(buffer, MAX_STRING_LENGTH, instr + 1);
}

void destP(const char* instr, char* buffer)
{
	if (containsP(instr, '='))
	{
		char dest[4];
		int pos = 0;
		while (*instr != '=')
			dest[pos++] = *(instr++);
		dest[pos] = '\0';
		strcpy_s(buffer, 4, dest);
	}
	else
		strcpy_s(buffer, 1, "");
}

void compP(const char* instr, char* buffer)
{
	char* start = strchr(instr, '='), *end = strchr(instr, ';');
	char temp[5];
	if (!start++) start = instr;
	if (!end--) end = instr + strlen(instr);
	int pos = 0;
	while (start <= end)
		temp[pos++] = *(start++);
	temp[pos] = '\0';
	strcpy_s(buffer, 5, temp);
}

void jumpP(const char* instr, char* buffer)
{
	if (containsP(instr, ';'))
	{
		char *ptr = strchr(instr, ';') + 1, temp[4];
		int i = 0;
		while (*ptr)
			temp[i++] = *(ptr++);
		temp[3] = '\0';
		strcpy_s(buffer, 4, temp);
	}
	else
		strcpy_s(buffer, 1, "");
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
	strcpy_s(buffer, MAX_INSTR_LENGTH, temp);
}

static bool containsP(const char* str, char c)
{
	for (; *str; str++)
		if (*str == c)
			return true;
	return false;
}

