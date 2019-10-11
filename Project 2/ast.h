/*
 *  File that holds the information about creating the functions for creating the
 *  abstract syntax tree.
 */

#ifndef AST_H
#define AST_H

#include <stddef.h>

/*
 *  All possible different types a node can have.
 *  Every Node will have exactly one type.
 */
enum NodeType {

  /* All Literals */
  NODETYPE_CONSTANT_INTEGER,           /*               Integer Literals             */
  NODETYPE_CONSTANT_STRING,            /*               String Literals              */
  NODETYPE_CONSTANT_CHARACTER,         /*              Character Literals            */
  NODETYPE_CONSTANT_TRUE,              /*                     True                   */
  NODETYPE_CONSTANT_FALSE,             /*                     False                  */
  NODETYPE_CONSTANT_NULL,              /*                     Null                   */

  /* All Control Flow */
  NODETYPE_CONTROL_IF_ELSE,            /*              If and possible Else          */
  NODETYPE_CONTROL_FOR,                /*              For Loop                      */
  NODETYPE_CONTROL_WHILE,              /*              While Loop                    */


  /* Variable Declarations */
  NODETYPE_VAR_DECL,                   /*             Variable Declaration           */
  NODETYPE_VAR_DECL_LIST,              /*        List of Variable Declarations       */

  /* Functions */
  NODETYPE_FUNC_DECL,                  /*             Function Decl and Def          */
  NODETYPE_FUNC_PARAMLIST,             /*             Function Parameters            */
  NODETYPE_FUNC_ARGLIST,               /*             Function Arguments             */

  /* Base Type */
  NODETYPE_TYPE,                       /*            Base Node for all types         */

  /* Type Options */
  NODETYPE_TYPE_BOOL,                  /*             Node for bool type             */
  NODETYPE_TYPE_INT,                   /*             Node for int type              */
  NODETYPE_TYPE_UINT,                  /*             Node for unsigned int type     */
  NODETYPE_TYPE_CHAR,                  /*             Node for char type             */
  NODETYPE_TYPE_UCHAR,                 /*             Node for unsigned char type    */
  NODETYPE_TYPE_STRUCT,                /*             Node for struct type           */
  NODETYPE_TYPE_POINTER,               /*             Node for a pointer             */
  NODETYPE_TYPE_ARR,                   /*             Node for an array              */

  /* Structs */
  NODETYPE_STRUCT_DEF,                 /*         Node for a struct definition       */

  /* Binary Expressions */
  NODETYPE_EXPR_BINARY_ADD,            /*            Node for addition               */
  NODETYPE_EXPR_BINARY_SUB,            /*            Node for subtraction            */
  NODETYPE_EXPR_BINARY_MULT,           /*            Node for multiplication         */
  NODETYPE_EXPR_BINARY_DIV,            /*            Node for division               */
  NODETYPE_EXPR_BINARY_REM,            /*            Node for remainder              */
  NODETYPE_EXPR_BINARY_LSHIFT,         /*            Node for left shift             */
  NODETYPE_EXPR_BINARY_RSHIFT,         /*            Node for right shift            */
  NODETYPE_EXPR_BINARY_EQUAL,          /*            Node for ==                     */
  NODETYPE_EXPR_BINARY_NOTEQUAL,       /*            Node for !=                     */
  NODETYPE_EXPR_BINARY_GREATEREQUAL,   /*            Node for >=                     */
  NODETYPE_EXPR_BINARY_GREATER,        /*            Node for >                      */
  NODETYPE_EXPR_BINARY_LESSEQUAL,      /*            Node for <=                     */
  NODETYPE_EXPR_BINARY_LESS,           /*            Node for <                      */
  NODETYPE_EXPR_BINARY_ANDAND,         /*            Node for logical and            */
  NODETYPE_EXPR_BINARY_OROR,           /*            Node for logical or             */
  NODETYPE_EXPR_BINARY_AND,            /*            Node for bitwise and            */
  NODETYPE_EXPR_BINARY_OR,             /*            Node for bitwise or             */
  NODETYPE_EXPR_BINARY_XOR,            /*            Node for bitwise xor            */

  /* Prefix Expressions */
  NODETYPE_EXPR_PREFIX_PLUSPLUS,       /*            Node for ++ expr                */
  NODETYPE_EXPR_PREFIX_MINUSMINUS,     /*            Node for -- expr                */
  NODETYPE_EXPR_PREFIX_NEGATE,         /*            Node for - expr                */
  NODETYPE_EXPR_PREFIX_ADDRESS,        /*            Node for & expr                 */
  NODETYPE_EXPR_PREFIX_DEREFERENCE,    /*            Node for * expr                 */
  NODETYPE_EXPR_PREFIX_NOTNOT,         /*            Node for ! expr                 */
  NODETYPE_EXPR_PREFIX_NOT,            /*            Node for ~ expr                 */

  /* Struct Expressions */
  NODETYPE_EXPR_STRUCT_DOT,            /*            Node for expr .                 */
  NODETYPE_EXPR_STRUCT_ARROW,          /*            Node for expr ->                */

  /* Postfix Expressions */
  NODETYPE_EXPR_POSTFIX_PLUSPLUS,      /*            Node for expr ++                */
  NODETYPE_EXPR_POSTFIX_MINUSMINUS,    /*            Node for expr --                */

  /* Other Expressions */
  NODETYPE_EXPR_CALL,                  /*            Node for call expressions       */
  NODETYPE_EXPR_CAST,                  /*            Node for cast expressions       */
  NODETYPE_EXPR_ASSIGN,                /*            Node for assignment             */
  NODETYPE_EXPR_EMPTY,                 /*            Node to for ignored code        */
  NODETYPE_EXPR_LIST,                  /*            Node for initializing lists     */
  NODETYPE_ID,                         /*            Node for Identifers             */
  NODETYPE_SIZEOF,                     /*            Node for sizeof                 */
  NODETYPE_OFFSETOF,                   /*            Node for offsetof               */

  /* Other Import Statements */
  NODETYPE_GLOBAL,                     /*            Node for Global Root            */
  NODETYPE_BLOCK,                      /*   Used to group together common clauses    */

  /* Other Inner Statements */
  NODETYPE_BREAK,                      /*                     Break                  */
  NODETYPE_CONTINUE,                   /*                    Continue                */
  NODETYPE_RETURN,                     /*                     Return                 */

  /* Error */
  NODETYPE_ERR                         /*                     Error                  */
};

/*
 *  Union that consists of any possible data that might be needed by a node.
 */
union NodeData {
  char* identifier;       /* Name of an identifier              */
  char* string;           /* Data for string literal            */
  char character;         /* Data for a character literal       */
  int integer;            /* Data for an integer literal        */
};

typedef struct ast {
  /* Essential for functionality */

  enum NodeType type;     /* What kind of node                  */
  union NodeData data;    /* Data needed for literals.          */
  struct ast** children;   /* Children of a given node           */
  size_t size;            /* How many children are there        */
  size_t capacity;        /* Memory allocated for children      */

  /* Information used for error reporting. */

  int linenum;            /* What line does this node start at. */
  char* filename;         /* What file is this node in.         */
} AST;

/* Functions to create the AST */

/*
 *  Creates a new AST from a given type filename and linenum. You should not
 *  assume that filename will remain a legal pointer after this function
 *  terminates.
 */
AST* MakeAST(enum NodeType type, char* filename, int linenum);

/*
 *  Helper functions to make errors without children.
 */
AST* MakeErrorAST(char* filename, int linenum);

/*
 *  Takes in a given AST and mallocs a new AST with the exact same details as the
 *  original. Again you should assume the original may be freed at any point
 *  after this function terminates.
 */
AST* CopyAST(AST* original);

/*
 *  Takes in an two ASTs and concatenates the two by making node a child
 *  of tree.
 */
void AppendAST(AST* tree, AST* node);

/*
 *  Takes in an AST that has had all of its children allocated and resizes
 *  the children member to conserve memory.
 */
void ReduceASTMem(AST* ast);

/*
 *  Frees the memory allocated by a single AST node.
 */
void FreeNode(AST* ast);

/*
 *  Frees all the memory allocated by an AST.
 */
void FreeAST(AST* ast);

#endif

