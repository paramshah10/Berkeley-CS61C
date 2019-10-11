#include <stdio.h>
#include "additional-instructions.h"

void EmitMULH(enum reg rd, enum reg rs1, enum reg rs2) {
  printf("mulh %s %s %s\n", regNames[rd], regNames[rs1], regNames[rs2]);
}

void EmitORI(enum reg rd, enum reg rs1, int imm) {
  printf("ori %s %s %d\n", regNames[rd], regNames[rs1], imm);
}

