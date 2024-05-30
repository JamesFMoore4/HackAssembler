#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "Table.h"

#define MAX_INSTR_LENGTH 256

typedef enum {A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION, NOT_INSTRUCTION} Type;

bool hasMoreLines(FILE* input);

Type instructionType(const char* instr);

void symbol(const char* instr, char* buffer);

void destP(const char* instr, char* buffer);

void compP(const char* instr, char* buffer);

void jumpP(const char* instr, char* buffer);

void trim(const char* instr, char* buffer);

static bool containsP(const char* str, char c);

