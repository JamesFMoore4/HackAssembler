#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum {A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION} Type;

bool hasMoreLines(FILE* input);

Type instructionType(char* instr);

void symbol(char* instr, char* buffer);

void destP(char* instr, char* buffer);

void compP(char* instr, char* buffer);

void jumpP(char* instr, char* buffer);

static bool containsP(const char* str, char c);


