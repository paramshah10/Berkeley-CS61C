/*
 *  File that holds the information about the declaration type, which is
 *  used to hold any variable declarations and proper scopes.
 */

#ifndef DECL_H
#define DECL_H

#include <stddef.h>

/*
 *  Types of Decls
 */
enum DeclGroup {
  DECL_VAR,           /* Variable                          */
  DECL_BUILTIN_TYPE,  /* bool, int, uint, char, and uchar  */
  DECL_STRUCT,        /* Declared Struct                   */
  DECL_FUNC_DEF,      /* Function fully defined            */
  DECL_FUNC_NO_DEF,   /* Function declaration without body */
  DECL_BLOCK,         /* Used for Blocks and Globals       */
  DECL_STR            /* Used for String Literals          */
};

/*
 *  Types of levels at which a declaration can be stored.
 */
enum DeclLevel {
  STRUCT,             /* Used for declarations of struct members.   */
  GLOBAL,             /* Used for declarations at the global level. */
  FUNCTION            /* Used for declarations inside functions.    */
};

/*
 *  Struct used to declare an element.
 */
typedef struct decl {
  enum DeclGroup group;         /* Used to identify the type of decl               */
  char* identifier;             /* Holds the name of the declaration               */
  int declCount;                /* Ctr for telling if a variable has been decl'd   */
  struct decl** types;          /* List of Decls to hold types                     */
  size_t* typePointers;         /* List of Number of pointers each type has        */
  size_t typeSize;              /* Number of type decls                            */
  size_t typeCapacity;          /* Memory allocated for types.                     */
  struct decl** children;       /* Used to track fields                            */
  size_t childrenSize;          /* Number of children                              */
  size_t childrenCapacity;      /* Memory allocated for children                   */
  struct decl* parent;          /* Pointer back to parent                          */
  int linenum;                  /* Linenumber the decl occurs on                   */
  char* filename;               /* File name the decl occurs in.                   */
  enum DeclLevel level;         /* Variable to track where a var should be offset  */
  int offset;                   /* Tracks how far offset a decl is.                */
  int alignment;                /* Tracks the number of bytes to align to.         */
  int dataSize;                 /* Tracks how many bytes a decl uses.              */
  int* arrValues;               /* Tracks the values for each array level.         */
  size_t arrTotal;              /* Takes how many array levels a decl has.         */
  char* contents;               /* Pointer to value to initialize to.              */
} Decl;

/*
 *  Takes in a group, identifier, count, parent Decl, linenum, filename, level,
 *  offset, datasize, alignment, if it is a global variable, in which case
 *  the actual contents need to be stored inside the decl, a ptr to array values,
 *  and the length of the array. It then creates a Decl initialized with those
 *  parameters and returns a ptr to the decl.
 */
Decl* CreateDecl(enum DeclGroup group, char* identifier, int count, Decl* parent, int line, char* filename,
                 enum DeclLevel level, int offset, int dataSize, int alignment, int isGlobal, int* arrValues,
                 size_t arrTotal);

/*
 *  Takes in a pointer to a declaration list, a pointer to its size,
 *  a pointer to its capacity, and a declaration, and appends the
 *  declaration to the declaration list, updating the size and possibly
 *  resizing if necessary.
 */
void AppendDecl(Decl*** declList, size_t* sizePtr, size_t* capacityPtr, Decl* decl);

/*
 *  Takes in a Declaration list of a particular size and two decls, old
 *  and new, and replaces old in the declaration list with new if it
 *  exists. Otherwise it does nothing.
 */
void ReplaceDecl (Decl * *declList, size_t size, Decl * new, Decl* old);

/*
 *  Helper function to replace a decl in a list after it has been realloc'd
 */
void UpdateDecl (Decl * *declList, size_t size, Decl * new, Decl* old);

/*
 *  Takes in an Decl that has been finished and resizes its typePointers
 *  and children fields to conserve memory.
 */
void ReduceDeclMem(Decl* decl);

/*
 *  Takes in a declaration and frees all memory allocated in the declaration
 *  and all of its children.
 */
void FreeDecl(Decl* decl);

/*
 *  Takes in a pointer to a decl_list, a pointer to its size, a pointer to its
 *  capacity, a decl, a pointer to a list of pointers totals, and a pointer
 *  value. Appends the decl to the decl list passed in and appends the pointer
 *  to the pointer list, updating the size and resizing as necessary.
 */
void AppendType(Decl*** declList, size_t* sizePtr, size_t* capacityPtr, Decl* decl, size_t** pointerList,
                size_t pointer);

#endif

