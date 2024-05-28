#include "Table.h"
#include "Parser.h"
#include "Code.h"

int main(int argc, char* argv[])
{
	char buffer[4];

	jumpP("D=D+;JGT", buffer);

	printf("%s", buffer);

	return 0;
}

