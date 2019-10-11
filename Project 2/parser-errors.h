/*
 *  File that contains the functions which assist with error messages and
 *  error tracking during parsing.
 */

#ifndef PARSER_ERRORS_H
#define PARSER_ERRORS_H

#include "ast.h"

/*
 *  Tracks if when we have run out of tokens. Used to prevent redundant error
 *  messages.
 */
extern int eofReached;

/*
 *  Used to track the name of the current file. This is show if an unexpect eof
 *  occurs we can determine in what file it occurred.
 */
extern char* currFilename;

/*
 *  Function that takes in an AST and determines if any error has occurred.
 *  Returns 0 if no errors are in the AST and otherwise returns a nonzero value.
 */
int CheckErrors(AST* ast);

/*
 *  Function that takes in an AST and determines if any errors
 *  occurred in its creation. In addition to the AST, the function also contains
 *  parameters 'is_for', which is true if the current node is a descendent of a
 *  For Loop node, and 'incorrect_returns' which is pointer to an integer. This
 *  value is only useful for descendent of a func decl node that contains a
 *  body (a function definition). It should point to 0 if the function always
 *  successfully returns and should be nonzero otherwise.
 *
 *  This function shouldreturn 0 if there are no errors and otherwise a nonzero
 *  value if there are ANY ERRORS. (Note that 'incorrect_returns' must be used to
 *  determine the return value of the function and simply setting it to the
 *  correct value will not be sufficient).
 *
 *  There are 4 types of errors:
 *
 *  1. An Error Node is present in the AST. This means an error occurred in
 *  parsing. There is no need to print any output message as one as already
 *  occurred during parsing.
 *
 *  2. A Break statement outside a for loop. If a Break statement is encountered while
 *  'is_for' is false then an error has occurred. You should display an output message to STDERR indicating the problem. This is not
 *  quired for grading but will be essential for debugging any tests you write.
 *
 *
 *  3. A Continue statement outside a for loop. If a Continue statement is encountered while
 *  'is_for' is false then an error has occurred. You should display an output message to STDERR
 *  indicating the problem. This is not required for grading but will be
 *  essential for debugging any tests you write.
 *
 *  Note: if you're interested in knowing /why/ we have to account for these errors
 *  specifically rather than have them be resolved by the parser like some other errors,
 *  check out the footnote in the spec.
 */
int CheckImproperStatements(AST* ast, int isLoop);

/*
 *  Generates the error message for when there are not enough tokens to continue
 *  parsing rules. It switches eofReached to 1 to prevent redundant print
 *  statements.
 */
void GenerateEofError();

/*
 *  Function to assist the output of error messages when a token is needed to
 *  complete a rule in the grammar but is not found.
 */
void GenerateErrorMessage(char* missing, char* filename, int linenum);

#endif

