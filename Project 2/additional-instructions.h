/*
 *  File used to add any instructions needed to complete code generation.
 *  Editting this file is completely optional. This file is intended to
 *  allow you to include any instructions that venus recognizes but we
 *  opted not to use in our implementation.
 */

#ifndef ADDITIONAL_INSTRUCTIONS_H
#define ADDITIONAL_INSTRUCTIONS_H

#include <stdint.h>
#include <stddef.h>
#include "instructions.h"

void EmitMULH(enum reg rd, enum reg rs1, enum reg rs2);

void EmitORI(enum reg rd, enum reg rs1, int imm);

#endif

