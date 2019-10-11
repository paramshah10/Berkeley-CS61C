/*
 *  File that contains the main code generation. It parses the DAST and Decls
 *  list and uses those values to make calls to Emit instructions and generate
 *  actual code.
 */

#ifndef CGEN_H
#define CGEN_H

#include <stddef.h>
#include "dast.h"
#include "decl.h"
#include "instructions.h"

/*
 *  Main function used to generate all of the code. It starts by first outputting
 *  any global variable declarations for the .data segment and then produces
 *  the .text segment.
 */
void GenerateCode(DAST* dast, char* filename, Decl* globalDecl);

/*
 *  Default process for any node that does not produce code or have an action
 *  other than recursing over its children.
 */
void ProcessDefault(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

/*
 *  Process function generating the result of a variable.
 */
void ProcessID(DAST* dast, char* startLabel, char* endLabel, int regBytes);

void ProcessConstTrue(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessConstFalse(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessConstInt(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessConstNull(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessExprBinaryMul(DAST* dast,

                          char* startLabel,
                          char* endLabel, int regBytes);

void ProcessExprBinaryDiv(DAST* dast,

                          char* startLabel,
                          char* endLabel, int regBytes);

void ProcessFuncDecl(DAST* dast, char* startLabel, char* endLabel, int regBytes);

void ProcessBlock(DAST* dast, char* startLabel, char* endLabel, int regBytes);


void ProcessFor(DAST* dast,  char* startLabel, char* endLabel, int regBytes);


void ProcessVarDecl(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessReturn(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessExprAssign(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessBreak(DAST* dast, char* startLabel, char* endLabel, int regBytes);

void ProcessContinue(DAST* dast, char* startLabel, char* endLabel, int regBytes);

/*
 *  Primary function that calls the appropriate code generation function for
 *  each node.
 */
void Dispatch(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

/*
 *  Dispatch function used for acquiring addresses.
 */
void DispatchLeft(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessLeftDot(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessLeftAarow(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessLeftID(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

void ProcessLeftDeref(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

#endif

