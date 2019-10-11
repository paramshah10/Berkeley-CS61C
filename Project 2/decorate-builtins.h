/*
 *  File used to hold the information about any builtin types and variables
 *  needed for initializing decoration.
 */

#ifndef DECORATE_BUILTINS_H
#define DECORATE_BUILTINS_H

#include "decl.h"

#define ERROR_STRING "__error__"
#define NULL_STRING "null"
#define BOOL_STRING "bool"
#define CHAR_STRING "char"
#define UCHAR_STRING "unsigned char"
#define INT_STRING "int"
#define UINT_STRING "unsigned int"

/* Number of builtin types + error and null. */
extern size_t builtinTotal;

/* Global List of all available types */
extern Decl** typeList;
extern size_t typeSize;
extern size_t typeCapacity;

/* Global List of all available functions */
extern Decl** funcList;
extern size_t funcSize;
extern size_t funcCapacity;

/*
 *  Global List of all decls that need to be freed
 *  and are not stored elsewhere.
 */
extern Decl** freeList;
extern size_t freeSize;
extern size_t freeCapacity;

/* Global Variable for error types */
extern Decl* errorType;

/* Global Variable for NULL */
extern Decl* nullType;

/* Global Variables for built in types */
extern Decl* boolType;
extern Decl* charType;
extern Decl* ucharType;
extern Decl* intType;
extern Decl* uintType;

/*
 *  Function used to initialize the builtin types and lists for the decorating
 *  step.
 */
void InitBuiltins(char* filename);

#endif

