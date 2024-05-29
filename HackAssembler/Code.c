#include "Code.h"

void dest(char* arg, char* buffer)
{
	if (arg[0] == '\0')
		strcpy_s(buffer, 4, "000");
	else if (!strcmp(arg, "M"))
		strcpy_s(buffer, 4, "001");
	else if (!strcmp(arg, "D"))
		strcpy_s(buffer, 4, "010");
	else if (!strcmp(arg, "DM"))
		strcpy_s(buffer, 4, "011");
	else if (!strcmp(arg, "A"))
		strcpy_s(buffer, 4, "100");
	else if (!strcmp(arg, "AM"))
		strcpy_s(buffer, 4, "101");
	else if (!strcmp(arg, "AD"))
		strcpy_s(buffer, 4, "110");
	else if (!strcmp(arg, "ADM"))
		strcpy_s(buffer, 4, "111");
}

void comp(char* arg, char* buffer)
{
	if (!strcmp(arg, "0"))
		strcpy_s(buffer, 8, "0101010");
	else if (!strcmp(arg, "1"))
		strcpy_s(buffer, 8, "0111111");
	else if (!strcmp(arg, "-1"))
		strcpy_s(buffer, 8, "0111010");
	else if (!strcmp(arg, "D"))
		strcpy_s(buffer, 8, "0001100");
	else if (!strcmp(arg, "A"))
		strcpy_s(buffer, 8, "0110000");
	else if (!strcmp(arg, "!D"))
		strcpy_s(buffer, 8, "0001101");
	else if (!strcmp(arg, "!A"))
		strcpy_s(buffer, 8, "0110001");
	else if (!strcmp(arg, "-D"))
		strcpy_s(buffer, 8, "0001111");
	else if (!strcmp(arg, "-A"))
		strcpy_s(buffer, 8, "0110011");
	else if (!strcmp(arg, "D+1"))
		strcpy_s(buffer, 8, "0011111");
	else if (!strcmp(arg, "A+1"))
		strcpy_s(buffer, 8, "0110111");
	else if (!strcmp(arg, "D-1"))
		strcpy_s(buffer, 8, "0001110");
	else if (!strcmp(arg, "A-1"))
		strcpy_s(buffer, 8, "0110010");
	else if (!strcmp(arg, "D+A"))
		strcpy_s(buffer, 8, "0000010");
	else if (!strcmp(arg, "D-A"))
		strcpy_s(buffer, 8, "0010011");
	else if (!strcmp(arg, "A-D"))
		strcpy_s(buffer, 8, "0000111");
	else if (!strcmp(arg, "D&A"))
		strcpy_s(buffer, 8, "0000000");
	else if (!strcmp(arg, "D|A"))
		strcpy_s(buffer, 8, "0010101");
	else if (!strcmp(arg, "M"))
		strcpy_s(buffer, 8, "1110000");
	else if (!strcmp(arg, "!M"))
		strcpy_s(buffer, 8, "1110001");
	else if (!strcmp(arg, "-M"))
		strcpy_s(buffer, 8, "1110011");
	else if (!strcmp(arg, "M+1"))
		strcpy_s(buffer, 8, "1110111");
	else if (!strcmp(arg, "M-1"))
		strcpy_s(buffer, 8, "1110010");
	else if (!strcmp(arg, "D+M"))
		strcpy_s(buffer, 8, "1000010");
	else if (!strcmp(arg, "D-M"))
		strcpy_s(buffer, 8, "1010011");
	else if (!strcmp(arg, "M-D"))
		strcpy_s(buffer, 8, "1000111");
	else if (!strcmp(arg, "D&M"))
		strcpy_s(buffer, 8, "1000000");
	else if (!strcmp(arg, "D|M"))
		strcpy_s(buffer, 8, "1010101");
}

void jump(char* arg, char* buffer)
{
	if (arg[0] == '\0')
		strcpy_s(buffer, 4, "000");
	else if (!strcmp(arg, "JGT"))
		strcpy_s(buffer, 4, "001");
	else if (!strcmp(arg, "JEQ"))
		strcpy_s(buffer, 4, "010");
	else if (!strcmp(arg, "JGE"))
		strcpy_s(buffer, 4, "011");
	else if (!strcmp(arg, "JLT"))
		strcpy_s(buffer, 4, "100");
	else if (!strcmp(arg, "JNE"))
		strcpy_s(buffer, 4, "101");
	else if (!strcmp(arg, "JLE"))
		strcpy_s(buffer, 4, "110");
	else if (!strcmp(arg, "JMP"))
		strcpy_s(buffer, 4, "111");
}

void itob(char* buffer, int address)
{
	char temp[16];
	temp[15] = '\0';
	for (int i = 0, power = 16384; i < 15; i++, power >>= 1)
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