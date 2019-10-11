/*
 *  File that holds all of the instructions used to generate code in the
 *  compiler. This contains all the instructions the staff used to produce
 *  the solution, as well as some additional instructions. You are welcome
 *  to use additional instructions and not use some of these instructions.
 *  Any new instructions should be added to additional-instructions.c and
 *  additional-instructions.h. You are not allowed to modify this file.
 */

#ifndef INST_H
#define INST_H

#include <stdint.h>
#include <stddef.h>

/*
 *  For loads and stores note that our inputs go:
 *  Register, Imm, Register and match:
 *  lw Register Imm(Register)
 */


/*
 *  Enum containing all of the possible register names that can be output by
 *  the compiler.
 */
enum reg {
  X0, FP, S1, S2, S3, S4, S5, S6, S7, S8, S9, S10, S11, T0, T1, T2, T3, T4, T5, SP, RA, GP, A0, A1
};

/*
 *  Global variable of register names used to map our enum of registers to
 *  strings for printing.
 */
extern const char* regNames[];

/*
 *  Produces the code for a label.
 */
void EmitLABEL(char* label);

/*
 *  Produces the code for a risc-v comment.
 */
void EmitCOMMENT(char* comment);

void EmitADDI(enum reg rd, enum reg rs, int imm);

void EmitADD(enum reg rd, enum reg rs1, enum reg rs2);

void EmitSUB(enum reg rd, enum reg rs1, enum reg rs2);

void EmitMUL(enum reg rd, enum reg rs1, enum reg rs2);

void EmitDIV(enum reg rd, enum reg rs1, enum reg rs2);

void EmitDIVU(enum reg rd, enum reg rs1, enum reg rs2);

void EmitREM(enum reg rd, enum reg rs1, enum reg rs2);

void EmitREMU(enum reg rd, enum reg rs1, enum reg rs2);

void EmitSLL(enum reg rd, enum reg rs1, enum reg rs2);

void EmitSLLI(enum reg rd, enum reg rs1, int imm);

void EmitSRL(enum reg rd, enum reg rs1, enum reg rs2);

void EmitSRAI(enum reg rd, enum reg rs1, int imm);

void EmitOR(enum reg rd, enum reg rs1, enum reg rs2);

void EmitXOR(enum reg rd, enum reg rs1, enum reg rs2);

void EmitXORI(enum reg rd, enum reg rs1, int imm);

void EmitAND(enum reg rd, enum reg rs1, enum reg rs2);

void EmitANDI(enum reg rd, enum reg rs1, int imm);

void EmitSW(enum reg rs1, int imm, enum reg rs2);

void EmitLW(enum reg rd, int imm, enum reg rs);

void EmitSB(enum reg rs1, int imm, enum reg rs2);

void EmitLB(enum reg rd, int imm, enum reg rs);

void EmitLBU(enum reg rd, int imm, enum reg rs);

void EmitSEQZ(enum reg rd, enum reg rs);

void EmitSNEZ(enum reg rd, enum reg rs);

void EmitSLT(enum reg rd, enum reg rs1, enum reg rs2);

void EmitSLTU(enum reg rd, enum reg rs1, enum reg rs2);

void EmitSLTIU(enum reg rd, enum reg rs1, int imm);

void EmitLA(enum reg rd, char* label);

void EmitLI(enum reg rd, int imm);

void EmitMV(enum reg rd, enum reg rs);

void EmitJAL(enum reg rd, char* label);

void EmitBEQ(enum reg rs1, enum reg rs2, char* label);

void EmitBNE(enum reg rs1, enum reg rs2, char* label);

void EmitBEQZ(enum reg rs, char* label);

void EmitBNEZ(enum reg rs, char* label);

void EmitJAL(enum reg rs, char* label);

void EmitJR(enum reg rs);

void EmitJ(char* label);

void EmitECALL();

void EmitBREAK();

/*
 *  Outputs a .text directive.
 */
void EmitTEXT();

/*
 *  Outputs a .data directive.
 */
void EmitDATA();

/*
 *  Outputs a .globl main directive.
 */
void EmitGLOBLMAIN();

/*
 *  Outputs a .word and a value.
 */
void EmitWORDVALUE(int64_t value);

/*
 *  Outputs a .word reference to a label.
 */
void EmitWORDLABEL(char* label);

/*
 *  Outputs the contents for a string as a series of bytes.
 */
void EmitSTRING(char* string);

#endif

