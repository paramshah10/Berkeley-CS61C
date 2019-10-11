/*
 *  File that holds the information about a dast, which is a conversion
 *  of the previous ast datastructure with more information.
 */

#ifndef DAST_H
#define DAST_H

#include <stddef.h>
#include "ast.h"
#include "decl.h"



/*
 *  Decorated AST that tracks where the element is declared.
 */
typedef struct dast {

/* INFORMATION FROM THE AST. */

  enum NodeType type;       /* What kind of node                  */
  union NodeData data;      /* Data needed for literals.          */
  struct dast** children;   /* Children of a given node           */
  size_t size;              /* How many children are there        */
  size_t capacity;          /* Memory allocated for children      */
  int linenum;              /* What line does this node start at. */
  char* filename;           /* What file is this node in.         */

/* UNIQUE TO DAST. */
  int declCount;            /* When the dast was encountered
                             *  relatively to various declarations */


  Decl* varDecl;            /* Pointer to declaration for this
                             *  dast node. This value is NULL if
                             *  this value does not apply to this
                             *  node (for example an operator).    */

  Decl* typeDecl;           /* Pointer to the declaration of the
                             *  type this node evaluates to. This
                             *  is most useful for tracking types
                             *  for things like operators and for
                             *  subsequently applying things like
                             *  pointer arithmetic. This value is
                             *  NULL for anything that does not
                             *  evaluate to a type.                */

  int typeDeclPtrCount;     /* Tracks how many pointers to the
                             *  type the node is.                  */

  int typeDeclArrCount;     /* Tracks how many arr of the type
                             *  the node is.                       */

} DAST;

/*
 *  Takes in an AST and count and returns a DAST derived from the AST.
 */
DAST* ConvertAST(AST* ast, int count);

/*
 *  Takes in an AST and count and returns a DAST, recursing over all children.
 *  This is used for error checking in arrays before declarations are finished.
 */
DAST* CreateFullDAST(AST* ast);

/*
 *  Creates a DAST from the necessary information. This is useful when
 *  creating DASTs directly for optimization purposes. It takes in a type
 *  linenum, filename, and declCount and creates a generic DAST node of that
 *  type. All appending, adding data, and compressing must occur outside this
 *  function.
 */
DAST* CreateDAST(enum NodeType type, int linenum, char* filename, int declCount);

/*
 *  Takes in an two DASTs and concatenates the two by making node a child
 *  of tree. This is used for optimizations when the tree needs to be
 *  directly manipulated.
 */
void AppendDAST(DAST* tree, DAST* node);

/*
 *  Takes in an DAST that has had all of its children allocated and resizes
 *  the children member to conserve memory.
 */
void ReduceDASTMem(DAST* dast);

/*
 *  Takes in a DAST node and free all memory allocated for that particular
 *  node. It does not recurse onto its children.
 */
void FreeDASTNode(DAST* dast);

/*
 *  Takes in a DAST node and free all memory allocated for the entire tree.
 */
void FreeDAST(DAST* dast);

#endif

