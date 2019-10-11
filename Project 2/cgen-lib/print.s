PrintString:
  addi sp sp -4
  sw ra 0(sp)
  lw a1 4(sp) 
  addi a0 x0 4
  ecall
  jal PrintNewline
  lw ra 0(sp)
  addi sp sp 4
  jr ra

PrintInt:
  addi sp sp -4
  sw ra 0(sp)
  lw a1 4(sp) 
  addi a0 x0 1
  ecall
  jal PrintNewline
  lw ra 0(sp)
  addi sp sp 4
  jr ra

PrintChar:
  addi sp sp -4
  sw ra 0(sp)
  lb a1 4(sp)
  andi a1 a1 0xff 
  addi a0 x0 11
  ecall
  jal PrintNewline
  lw ra 0(sp)
  addi sp sp 4
  jr ra

PrintBool:
  addi sp sp -4
  sw ra 0(sp)
  lw a1 4(sp) 
  addi a0 x0 1
  ecall
  jal PrintNewline
  lw ra 0(sp)
  addi sp sp 4
  jr ra

PrintNewline:
  addi a1 x0 10 #Load newline char
  addi a0 x0 11
  ecall
  mv a0 x0
  jr ra

PrintInts:
  addi sp sp -8
  sw ra 4(sp)
  lw t0 8(sp)
  sw t0 0(sp)
  jal PrintInt
  lw t0 12(sp)
  sw t0 0(sp)
  jal PrintInt
  lw t0 16(sp)
  sw t0 0(sp)
  jal PrintInt
  lw ra 4(sp)
  addi sp sp 8
  jr ra

PrintChars:
  addi sp sp -8
  sw ra 4(sp)
  lb t0 8(sp)
  sb t0 0(sp)
  jal PrintChar
  lb t0 9(sp)
  sb t0 0(sp)
  jal PrintChar
  lb t0 10(sp)
  sb t0 0(sp)
  jal PrintChar
  lw ra 4(sp)
  addi sp sp 8
  jr ra
  

PrintMixed:
  addi sp sp -8
  sw ra 4(sp)
  lb t0 8(sp)
  sb t0 0(sp)
  jal PrintChar
  lb t0 9(sp)
  sb t0 0(sp)
  jal PrintChar
  lw t0 12(sp)
  sw t0 0(sp)
  jal PrintInt
  lw t0 16(sp)
  sw t0 0(sp)
  jal PrintInt
  lb t0 20(sp)
  sb t0 0(sp)
  jal PrintChar
  lw t0 24(sp)
  sw t0 0(sp)
  jal PrintInt
  lw ra 4(sp)
  addi sp sp 8
  jr ra
  
