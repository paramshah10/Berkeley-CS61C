/*
 *  File that contains the code students need to complete for the code
 *  generation step. This code interacts with the rest of code generation,
 *  which is abstracted away, in order to produce complete code files.
 */

#ifndef STUDENT_CGEN_H
#define STUDENT_CGEN_H

#include <stddef.h>
#include "dast.h"
#include "decl.h"
#include "instructions.h"

/*
 *  Code used to generate the negate expression. This is complete and is
 *  included to provide you an example of code generation.
 *
 *  Note how it calls dispatch on its child to recurse into generate code
 *  that needs to be negated. Then it cause apply its operation to the value
 *  of register S1 because we assume our most recent output is always in S1.
 *  Finally it places it own result in S1.
 */
void ProcessExprPrefixNegate(DAST* dast,
                             char* startLabel,
                             char* endLabel, int regBytes);

/*
 *  Helper function used to ease maintaining the our latest value in S1 invariant
 *  for binary expression. It returns an enum value which contains the value of
 *  the register used to hold a value the first of the two expresions,
 *  (the second is defined to be in s1).
 *
 *  You should use the enum values in instructions.h
 */
enum reg SetupBinaryInvariant(DAST* dast, char* startLabel, char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all & expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  No type checking should be necessary for this operator.
 */
void ProcessExprBinaryBitAnd(DAST* dast,

                             char* startLabel,
                             char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all | expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  No type checking should be necessary for this operator.
 */
void ProcessExprBinaryBitOr(DAST* dast,

                            char* startLabel,
                            char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all ^ expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  No type checking should be necessary for this operator.
 */
void ProcessExprBinaryBitXor(DAST* dast,

                             char* startLabel,
                             char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all && expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  An operand is considered to have a true value if it is nonzero and a false
 *  value if it is 0.
 *
 *  If the condition is met then you should produce 1. If the condition is not
 *  met not then you should produce 0. Failure to return either of these two
 *  values exactly may result in a loss of credit, regardless of the truthiness
 *  of the values returned being correct.
 */
void ProcessExprBinaryLogicAnd(DAST* dast,

                               char* startLabel,
                               char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all || expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  An operand is considered to have a true value if it is nonzero and a false
 *  value if it is 0.
 *
 *  If the condition is met then you should produce 1. If the condition is not
 *  met not then you should produce 0. Failure to return either of these two
 *  values exactly may result in a loss of credit, regardless of the truthiness
 *  of the values returned being correct.
 */
void ProcessExprBinaryLogicOr(DAST* dast,

                              char* startLabel,
                              char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all == expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  For equality you should not need to consider the types of the operands at all
 *  and simply need to determine if the results are equal.
 *
 *  If the condition is met then you should produce 1. If the condition is not
 *  met not then you should produce 0. Failure to return either of these two
 *  values exactly may result in a loss of credit, regardless of the truthiness
 *  of the values returned being correct.
 */
void ProcessExprBinaryEq(DAST* dast,

                         char* startLabel,
                         char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all != expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  For equality you should not need to consider the types of the operands at all
 *  and simply need to determine if the results are equal.
 *
 *  If the condition is met then you should produce 1. If the condition is not
 *  met not then you should produce 0. Failure to return either of these two
 *  values exactly may result in a loss of credit, regardless of the truthiness
 *  of the values returned being correct.
 */
void ProcessExprBinaryNotEq(DAST* dast,

                            char* startLabel,
                            char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all add expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  Add needs to handle both normal arithmetic and pointer arithmetic. As a
 *  refresher in C adding to a pointer increments the address by one
 *  element in size. For example if we have
 *
 *  x + 1
 *
 *  where x is an int *, then x + 1 produces x + sizeof (int) * 1 in assembly.
 *
 *  To handle this case you should use c1PtrTotal and c2PtrTotal to determine
 *  if either child is a pointer (only 1 will ever be a pointer and you do not
 *  need to check this condition). Then you will need to determine the sizeof
 *  amount. Our compiler organizes types as having a typeDecl, which contains
 *  a base type (like int), and a pointer counter, which roughly indicates how
 *  many *s there are. To find the size of the base type, you should look at
 *  the child1/2->typeDecl->dataSize.
 */
void ProcessExprBinaryAdd(DAST* dast,

                          char* startLabel,
                          char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all sub expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  Add needs to handle both normal subtraction, pointer arithmetic and
 *  subtracting one pointer from another. As a refresher in C adding to a pointer
 *  decrements the address by one element in size. For example if we have
 *
 *  x - 1
 *
 *  where x is an int *, then x - 1 produces x - sizeof (int) * 1 in assembly.
 *
 *  To handle this case you should use c1PtrTotal and c2PtrTotal to determine
 *  if either child is a pointer. Then you will need to determine the sizeof
 *  amount. Our compiler organizes types as having a typeDecl, which contains
 *  a base type (like int), and a pointer counter, which roughly indicates how
 *  many *s there are. To find the size of the base type, you should look at
 *  the child1/2->typeDecl->dataSize.
 *
 *  In addition you also need to consider the case where two pointers are
 *  being subtracted from each other. For example:
 *
 *  (x + 2) - x = 2
 *
 *  regardless of the actual distance between the addresses in x and x + 2.
 *  Once again you will need the pointer count and/or the dataSize to complete
 *  this step.
 */
void ProcessExprBinarySub(DAST* dast,

                          char* startLabel,
                          char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all >= expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  For comparison operations the type of the operator is important for selecting
 *  the correct comparison instruction. In particular we are concerned with two
 *  types of comparisons:
 * signed
 * unsigned
 *
 *  To determine when to select which type of comparison, we have two conditions.
 *  First if we are working with pointers, both pointers must be the same type
 *  and c1PtrTotal/c2PtrTotal will be > 0. All pointer comparisons are unsigned.
 *  The other possibility is that we are working with an integer type. There are
 *  5 integer types and they can be determined by comparing child1/2->typedecl
 *  directly with some global variables (use ==). These types are:
 *
 *   1. unsigned int (global variable: uintType), unsigned
 *   2. int (global variable: intType), signed
 *   3. unsigned char (global variable: ucharType), unsigned
 *   4. char (global variable: charType), signed
 *   5. NULL (global variable: nullType), signed/unsigned (doesn't matter)
 *
 *  For our comparisons we select the signedness (signed or unsigned) of the
 *  highest priority operand (unsigned int is highest, NULL is lowest). So for
 *  example if we had:
 *
 *  x >= y
 *
 *  where x is a char and y is an unsigned int, then we would do an unsigned
 *  comparison because unsigned int is higher priority than char. Do not worry
 *  about making the sizes of the operands the same, this is handled for you by
 *  the starter code.
 *
 *  If the condition is met then you should produce 1. If the condition is not
 *  met not then you should produce 0. Failure to return either of these two
 *  values exactly may result in a loss of credit, regardless of the truthiness
 *  of the values returned being correct.
 */
void ProcessExprBinaryGTEq(DAST* dast,

                           char* startLabel,
                           char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all > expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  For comparison operations the type of the operator is important for selecting
 *  the correct comparison instruction. In particular we are concerned with two
 *  types of comparisons:
 * signed
 * unsigned
 *
 *  To determine when to select which type of comparison, we have two conditions.
 *  First if we are working with pointers, both pointers must be the same type
 *  and c1PtrTotal/c2PtrTotal will be > 0. All pointer comparisons are unsigned.
 *  The other possibility is that we are working with an integer type. There are
 *  5 integer types and they can be determined by comparing child1/2->typedecl
 *  directly with some global variables (use ==). These types are:
 *
 *   1. unsigned int (global variable: uintType), unsigned
 *   2. int (global variable: intType), signed
 *   3. unsigned char (global variable: ucharType), unsigned
 *   4. char (global variable: charType), signed
 *   5. NULL (global variable: nullType), signed/unsigned (doesn't matter)
 *
 *  For our comparisons we select the signedness (signed or unsigned) of the
 *  highest priority operand (unsigned int is highest, NULL is lowest). So for
 *  example if we had:
 *
 *  x > y
 *
 *  where x is a char and y is an unsigned int, then we would do an unsigned
 *  comparison because unsigned int is higher priority than char. Do not worry
 *  about making the sizes of the operands the same, this is handled for you by
 *  the starter code.
 *
 *  If the condition is met then you should produce 1. If the condition is not
 *  met not then you should produce 0. Failure to return either of these two
 *  values exactly may result in a loss of credit, regardless of the truthiness
 *  of the values returned being correct.
 */
void ProcessExprBinaryGT(DAST* dast,

                         char* startLabel,
                         char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all <= expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  For comparison operations the type of the operator is important for selecting
 *  the correct comparison instruction. In particular we are concerned with two
 *  types of comparisons:
 * signed
 * unsigned
 *
 *  To determine when to select which type of comparison, we have two conditions.
 *  First if we are working with pointers, both pointers must be the same type
 *  and c1PtrTotal/c2PtrTotal will be > 0. All pointer comparisons are unsigned.
 *  The other possibility is that we are working with an integer type. There are
 *  5 integer types and they can be determined by comparing child1/2->typedecl
 *  directly with some global variables (use ==). These types are:
 *
 *   1. unsigned int (global variable: uintType), unsigned
 *   2. int (global variable: intType), signed
 *   3. unsigned char (global variable: ucharType), unsigned
 *   4. char (global variable: charType), signed
 *   5. NULL (global variable: nullType), signed/unsigned (doesn't matter)
 *
 *  For our comparisons we select the signedness (signed or unsigned) of the
 *  highest priority operand (unsigned int is highest, NULL is lowest). So for
 *  example if we had:
 *
 *  x <= y
 *
 *  where x is a char and y is an unsigned int, then we would do an unsigned
 *  comparison because unsigned int is higher priority than char. Do not worry
 *  about making the sizes of the operands the same, this is handled for you by
 *  the starter code.
 *
 *  If the condition is met then you should produce 1. If the condition is not
 *  met not then you should produce 0. Failure to return either of these two
 *  values exactly may result in a loss of credit, regardless of the truthiness
 *  of the values returned being correct.
 */
void ProcessExprBinaryLTEq(DAST* dast,

                           char* startLabel,
                           char* endLabel, int regBytes);

/*
 *  Function used to handle code generation for all < expressions. As with all
 *  binary expressions it relies on the binary invariant completed in part 1.
 *
 *  For comparison operations the type of the operator is important for selecting
 *  the correct comparison instruction. In particular we are concerned with two
 *  types of comparisons:
 * signed
 * unsigned
 *
 *  To determine when to select which type of comparison, we have two conditions.
 *  First if we are working with pointers, both pointers must be the same type
 *  and c1PtrTotal/c2PtrTotal will be > 0. All pointer comparisons are unsigned.
 *  The other possibility is that we are working with an integer type. There are
 *  5 integer types and they can be determined by comparing child1/2->typedecl
 *  directly with some global variables (use ==). These types are:
 *
 *   1. unsigned int (global variable: uintType), unsigned
 *   2. int (global variable: intType), signed
 *   3. unsigned char (global variable: ucharType), unsigned
 *   4. char (global variable: charType), signed
 *   5. NULL (global variable: nullType), signed/unsigned (doesn't matter)
 *
 *  For our comparisons we select the signedness (signed or unsigned) of the
 *  highest priority operand (unsigned int is highest, NULL is lowest). So for
 *  example if we had:
 *
 *  x < y
 *
 *  where x is a char and y is an unsigned int, then we would do an unsigned
 *  comparison because unsigned int is higher priority than char. Do not worry
 *  about making the sizes of the operands the same, this is handled for you by
 *  the starter code.
 *
 *  If the condition is met then you should produce 1. If the condition is not
 *  met not then you should produce 0. Failure to return either of these two
 *  values exactly may result in a loss of credit, regardless of the truthiness
 *  of the values returned being correct.
 */
void ProcessExprBinaryLT(DAST* dast,

                         char* startLabel,
                         char* endLabel, int regBytes);

/*
 *  Helper function for decrementing the stack and storing any registers
 *  that need to be saved. NOTE that you DO NOT know what code will be
 *  Generated after the function declaration and in fact we have hid some
 *  of the code from you.
 *
 *  As a result, you should save every register that calling convention
 *  dictates may need to be restored (look at lecture slides if you
 *  are not sure which registers may need to be restored).
 *
 *  The starter code has already saved the Frame Pointer (S0/FP), so you
 *  do NOT need to save that register.
 *
 *  This function returns the number of bytes the stack was decremented
 *  by. It should always return a non-negative value.
 */
size_t SaveRegisters();

/*
 *  Helper function for restoring all saved registers. You may assume that the
 *  stack pointer is currently located at the value it was set to when modified
 *  in SaveRegisters ().
 */
void RestoreRegisters();

/*
 *  Function used to generate call expressions. It decrements the stack to
 *  allocate space for the arguments, places the arguments on the stack and
 *  then switches control to the function it calls. On return it moves the
 *  output to our S1, our invariant register and restores the stack to its
 *  previous state.
 *
 *  To determine where to place arugments you should use the values in offsets
 *  and to determine how large of a value to store (either word or byte) you
 *  should use the results in sizes.
 */
void ProcessExprCall(DAST* dast, char* startLabel, char* endLabel, int regBytes);

/*
 *  Function used for generating code for all if/else expressions. This code
 *  produces labels that should be used to navigate which code block to execute
 *  as a result of the condition provided. None of these labels should change
 *  the start or end label because those values are used for the starts and
 *  ends of loops.
 */
void ProcessIfElse(DAST* dast,  char* startLabel, char* endLabel, int regBytes);

/*
 *  Function used for generating code for all while expressions. This code
 *  produces labels that should be used to navigate which code block to execute
 *  as a result of the condition provided return to the condition when the end
 *  of the loop is reached. In any recursive calls you should replace startLabel
 *  with the label used at the start of the loop and endWhile with the label
 *  used at the end of the loop.
 */
void ProcessWhile(DAST* dast, char* startLabel, char* endLabel, int regBytes);

#endif

