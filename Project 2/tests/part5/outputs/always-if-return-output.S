.globl main
.data
__str__0:
.byte 104
.byte 101
.byte 108
.byte 108
.byte 111
.byte 32
.byte 119
.byte 111
.byte 114
.byte 108
.byte 100
.byte 0
.text
f:
addi sp sp -4
sw fp 0(sp)
mv fp sp
addi sp sp -48
sw ra 0(sp)
sw s1 4(sp)
sw s2 8(sp)
sw s3 12(sp)
sw s4 16(sp)
sw s5 20(sp)
sw s6 24(sp)
sw s7 28(sp)
sw s8 32(sp)
sw s9 36(sp)
sw s10 40(sp)
sw s11 44(sp)
addi s1 x0 1
beq s1 x0 __label__0
li s1 1
mv a0 s1
j _f
__label__0:
_f:
addi sp fp -48
lw s11 44(sp)
lw s10 40(sp)
lw s9 36(sp)
lw s8 32(sp)
lw s7 28(sp)
lw s6 24(sp)
lw s5 20(sp)
lw s4 16(sp)
lw s3 12(sp)
lw s2 8(sp)
lw s1 4(sp)
lw ra 0(sp)
addi sp sp 48
lw fp 0(sp)
addi sp sp 4
jr ra
g:
addi sp sp -4
sw fp 0(sp)
mv fp sp
addi sp sp -48
sw ra 0(sp)
sw s1 4(sp)
sw s2 8(sp)
sw s3 12(sp)
sw s4 16(sp)
sw s5 20(sp)
sw s6 24(sp)
sw s7 28(sp)
sw s8 32(sp)
sw s9 36(sp)
sw s10 40(sp)
sw s11 44(sp)
li s1 1
beq s1 x0 __label__2
li s1 1
mv a0 s1
j _g
__label__2:
_g:
addi sp fp -48
lw s11 44(sp)
lw s10 40(sp)
lw s9 36(sp)
lw s8 32(sp)
lw s7 28(sp)
lw s6 24(sp)
lw s5 20(sp)
lw s4 16(sp)
lw s3 12(sp)
lw s2 8(sp)
lw s1 4(sp)
lw ra 0(sp)
addi sp sp 48
lw fp 0(sp)
addi sp sp 4
jr ra
h:
addi sp sp -4
sw fp 0(sp)
mv fp sp
addi sp sp -48
sw ra 0(sp)
sw s1 4(sp)
sw s2 8(sp)
sw s3 12(sp)
sw s4 16(sp)
sw s5 20(sp)
sw s6 24(sp)
sw s7 28(sp)
sw s8 32(sp)
sw s9 36(sp)
sw s10 40(sp)
sw s11 44(sp)
addi s1 x0 99
beq s1 x0 __label__4
li s1 1
mv a0 s1
j _h
__label__4:
_h:
addi sp fp -48
lw s11 44(sp)
lw s10 40(sp)
lw s9 36(sp)
lw s8 32(sp)
lw s7 28(sp)
lw s6 24(sp)
lw s5 20(sp)
lw s4 16(sp)
lw s3 12(sp)
lw s2 8(sp)
lw s1 4(sp)
lw ra 0(sp)
addi sp sp 48
lw fp 0(sp)
addi sp sp 4
jr ra
i:
addi sp sp -4
sw fp 0(sp)
mv fp sp
addi sp sp -48
sw ra 0(sp)
sw s1 4(sp)
sw s2 8(sp)
sw s3 12(sp)
sw s4 16(sp)
sw s5 20(sp)
sw s6 24(sp)
sw s7 28(sp)
sw s8 32(sp)
sw s9 36(sp)
sw s10 40(sp)
sw s11 44(sp)
la s1 __str__0
beq s1 x0 __label__6
li s1 1
mv a0 s1
j _i
__label__6:
_i:
addi sp fp -48
lw s11 44(sp)
lw s10 40(sp)
lw s9 36(sp)
lw s8 32(sp)
lw s7 28(sp)
lw s6 24(sp)
lw s5 20(sp)
lw s4 16(sp)
lw s3 12(sp)
lw s2 8(sp)
lw s1 4(sp)
lw ra 0(sp)
addi sp sp 48
lw fp 0(sp)
addi sp sp 4
jr ra
m:
addi sp sp -4
sw fp 0(sp)
mv fp sp
addi sp sp -48
sw ra 0(sp)
sw s1 4(sp)
sw s2 8(sp)
sw s3 12(sp)
sw s4 16(sp)
sw s5 20(sp)
sw s6 24(sp)
sw s7 28(sp)
sw s8 32(sp)
sw s9 36(sp)
sw s10 40(sp)
sw s11 44(sp)
addi s1 x0 0
beq s1 x0 __label__8
li s1 1
mv a0 s1
j _m
__label__8:
li s1 2
mv a0 s1
j _m
_m:
addi sp fp -48
lw s11 44(sp)
lw s10 40(sp)
lw s9 36(sp)
lw s8 32(sp)
lw s7 28(sp)
lw s6 24(sp)
lw s5 20(sp)
lw s4 16(sp)
lw s3 12(sp)
lw s2 8(sp)
lw s1 4(sp)
lw ra 0(sp)
addi sp sp 48
lw fp 0(sp)
addi sp sp 4
jr ra
main:
addi sp sp -4
sw fp 0(sp)
mv fp sp
addi sp sp -48
sw ra 0(sp)
sw s1 4(sp)
sw s2 8(sp)
sw s3 12(sp)
sw s4 16(sp)
sw s5 20(sp)
sw s6 24(sp)
sw s7 28(sp)
sw s8 32(sp)
sw s9 36(sp)
sw s10 40(sp)
sw s11 44(sp)
jal ra f
mv s1 a0
addi sp sp -4
sw s1 0(sp)
jal ra g
mv s1 a0
lw s2 0(sp)
addi sp sp 4
add s1 s1 s2
addi sp sp -4
sw s1 0(sp)
jal ra h
mv s1 a0
lw s2 0(sp)
addi sp sp 4
add s1 s1 s2
addi sp sp -4
sw s1 0(sp)
jal ra i
mv s1 a0
lw s2 0(sp)
addi sp sp 4
add s1 s1 s2
addi sp sp -4
sw s1 0(sp)
jal ra m
mv s1 a0
lw s2 0(sp)
addi sp sp 4
add s1 s1 s2
mv a0 s1
j _main
_main:
addi sp fp -48
lw s11 44(sp)
lw s10 40(sp)
lw s9 36(sp)
lw s8 32(sp)
lw s7 28(sp)
lw s6 24(sp)
lw s5 20(sp)
lw s4 16(sp)
lw s3 12(sp)
lw s2 8(sp)
lw s1 4(sp)
lw ra 0(sp)
addi sp sp 48
lw fp 0(sp)
addi sp sp 4
mv a1 a0
addi a0 x0 17
ecall
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
  
