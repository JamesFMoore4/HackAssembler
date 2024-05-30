#include "Code.h"

char* destarg[] =
{
	"",
	"M",
	"D",
	"DM",
	"A",
	"AM",
	"AD",
	"ADM"
};

char* destinstr[] =
{
	"000",
	"001",
	"010",
	"011",
	"100",
	"101",
	"110",
	"111"
};

char* comparg[] =
{
	"0",
	"1",
	"-1",
	"D",
	"A",
	"!D",
	"!A",
	"-D",
	"-A",
	"D+1",
	"A+1",
	"D-1",
	"A-1",
	"D+A",
	"D-A",
	"A-D",
	"D&A",
	"D|A",
	"M",
	"!M",
	"-M",
	"M+1",
	"M-1",
	"D+M",
	"D-M",
	"M-D",
	"D&M",
	"D|M"
};

char* compinstr[] =
{
	"0101010",
	"0111111",
	"0111010",
	"0001100",
	"0110000",
	"0001101",
	"0110001",
	"0001111",
	"0110011",
	"0011111",
	"0110111",
	"0001110",
	"0110010",
	"0000010",
	"0010011",
	"0000111",
	"0000000",
	"0010101",
	"1110000",
	"1110001",
	"1110011",
	"1110111",
	"1110010",
	"1000010",
	"1010011",
	"1000111",
	"1000000",
	"1010101"
};

char* jumparg[] =
{
	"",
	"JGT",
	"JEQ",
	"JGE",
	"JLT",
	"JNE",
	"JLE",
	"JMP"
};

char* jumpinstr[] =
{
	"000",
	"001",
	"010",
	"011",
	"100",
	"101",
	"110",
	"111"
};

void dest(char* arg, char* buffer)
{
	for (int i = 0; i < 8; i++)
		if (!strcmp(destarg[i], arg))
			strcpy_s(buffer, 4, destinstr[i]);
}

void comp(char* arg, char* buffer)
{
	for (int i = 0; i < 28; i++)
		if (!strcmp(comparg[i], arg))
			strcpy_s(buffer, 8, compinstr[i]);
}

void jump(char* arg, char* buffer)
{
	for (int i = 0; i < 8; i++)
		if (!strcmp(jumparg[i], arg))
			strcpy_s(buffer, 4, jumpinstr[i]);
}

void itob(char* buffer, int address)
{
	char temp[16];
	temp[15] = '\0';
	for (int i = 0, power = (int)pow(2, 14); i < 15; i++, power >>= 1)
	{
		if (address - power >= 0)
		{
			temp[i] = '1';
			address -= power;
		}
		else
			temp[i] = '0';
	}
	strcpy_s(buffer, sizeof(temp), temp);
}

bool isValidPath(char* path)
{
	size_t pathlen = strlen(path);
	if (pathlen < 5)
		return false;

	char* extension = path + pathlen - 4;
	if (strcmp(extension, ".asm"))
		return false;

	return true;
}