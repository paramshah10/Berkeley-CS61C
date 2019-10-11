/*
 *  File that contains functions used to assist in code generation but none of
 *  the actual code generation.
 */

#ifndef CGEN_HELPERS_H
#define CGEN_HELPERS_H

#include "dast.h"
#include "instructions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct stringLabelMap {
  char* string;
  char* label;
  struct stringLabelMap* next;
} stringLabelMap;

extern stringLabelMap* s;

/*
 *  Helper function to free the associated memory with the list of string
 *  literals.
 */
void FreeStringList(stringLabelMap* lst);

/*
 *  Helper function to create a local label that can be used anywhere in a file.
 *  This is intended for jumps that are required inside of functions and not for
 *  function labels.
 */
char* GenerateLocalLabel();

/*
 *  Used to create a string used to refer to a label at the end of functions
 *  for return statements.
 */
char* GenerateFunctionEndLabel(char* funcName);

/*
 *  Creates a new string label for the given string and adds to the
 *  stringLabelMap s
 */
char* GenerateStringLabel(char* str);

/*
 *  Helper function that outputs the code for creating a string literal. It makes
 *  a call to one of the emits in instructions.h
 */
void GenerateString(Decl* curr);

/*
 *  Helper function that outputs a data value and pads 0s to the end of it.
 */
void GenerateDataValue(int64_t value, size_t dataSize);

/*
 *  Helper function used to start the data section.
 */
void GenerateDataLabel(char* label, size_t dataSize);

/*
 *  Helper function used to output labels for global variables.
 */
char* GenerateVarLabel();

/*
 *  Helper function used to locate the label for a string literal.
 */
char* GetStringLabel(stringLabelMap* temp, char* str);

/*
 *  Helper function used to ensure the output of an operation fits inside/matches
 *  its type specifications.
 */
void ApplyTypeRules(DAST* dast, enum reg S1);

/*
 *  Helper function used to make sure comparisons occur with proper width for
 *  binary expressions.
 */
void MatchSizes(DAST* child1, enum reg child1Reg, DAST* child2, enum reg child2Reg);

/*
 *  Helper functions to determine how much to allocate on the stack for call
 *  expressions and where to place the arguments.
 */
size_t ComputeArgLocations(Decl* funcDecl, size_t* offsets, size_t* sizes);

#endif

