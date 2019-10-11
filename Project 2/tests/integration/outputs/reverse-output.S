.globl main
.data
.text
reverse_in_place:
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
addi sp sp -8
addi s1 fp -56
addi sp sp -4
sw s1 0(sp)
li s1 0
lw t0 0(sp)
sw s1 0(t0)
addi sp sp 4
j __label__1
__label__0:
addi s1 fp -56
mv s2 s1
lw s1 0(s2)
addi s3 s1 1
sw s3 0(s2)
__label__1:
addi s1 fp -56
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
addi s1 fp 8
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
li s1 2
lw s2 0(sp)
addi sp sp 4
div s1 s2 s1
lw s2 0(sp)
addi sp sp 4
slt s1 s2 s1
xori s1 s1 1
seqz s1 s1
beqz s1 __label__2
addi s1 fp -52
addi sp sp -4
sw s1 0(sp)
addi s1 fp 4
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
addi s1 fp -56
lw s1 0(s1)
lw s2 0(sp)
addi sp sp 4
addi t0 x0 1
li t1 1
mul t1 s1 t0
add s2 s2 t1
mv s1 s2
lb s1 0(s1)
lw t0 0(sp)
sw s1 0(t0)
addi sp sp 4
addi s1 fp 4
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
addi s1 fp -56
lw s1 0(s1)
lw s2 0(sp)
addi sp sp 4
addi t0 x0 1
li t1 1
mul t1 s1 t0
add s2 s2 t1
mv s1 s2
addi sp sp -4
sw s1 0(sp)
addi s1 fp 4
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
addi s1 fp 8
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
li s1 1
lw s2 0(sp)
addi sp sp 4
sub s1 s2 s1
addi sp sp -4
sw s1 0(sp)
addi s1 fp -56
lw s1 0(s1)
lw s2 0(sp)
addi sp sp 4
sub s1 s2 s1
lw s2 0(sp)
addi sp sp 4
addi t0 x0 1
li t1 1
mul t1 s1 t0
add s2 s2 t1
mv s1 s2
lb s1 0(s1)
lw t0 0(sp)
sb s1 0(t0)
addi sp sp 4
addi s1 fp 4
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
addi s1 fp 8
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
li s1 1
lw s2 0(sp)
addi sp sp 4
sub s1 s2 s1
addi sp sp -4
sw s1 0(sp)
addi s1 fp -56
lw s1 0(s1)
lw s2 0(sp)
addi sp sp 4
sub s1 s2 s1
lw s2 0(sp)
addi sp sp 4
addi t0 x0 1
li t1 1
mul t1 s1 t0
add s2 s2 t1
mv s1 s2
addi sp sp -4
sw s1 0(sp)
addi s1 fp -52
lw s1 0(s1)
lw t0 0(sp)
sb s1 0(t0)
addi sp sp 4
j __label__0
__label__2:
li s1 0
mv a0 s1
j _reverse_in_place
addi sp sp 8
_reverse_in_place:
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
addi sp sp -20
li s1 10
sw s1 -52(fp)
li s1 1
sb s1 -62(fp)
li s1 2
sb s1 -61(fp)
li s1 3
sb s1 -60(fp)
li s1 4
sb s1 -59(fp)
li s1 5
sb s1 -58(fp)
li s1 6
sb s1 -57(fp)
li s1 7
sb s1 -56(fp)
li s1 8
sb s1 -55(fp)
li s1 9
sb s1 -54(fp)
li s1 10
sb s1 -53(fp)
addi s1 fp -68
addi sp sp -4
sw s1 0(sp)
li s1 0
lw t0 0(sp)
sw s1 0(t0)
addi sp sp 4
j __label__4
__label__3:
addi s1 fp -68
mv s2 s1
lw s1 0(s2)
addi s3 s1 1
sw s3 0(s2)
__label__4:
addi s1 fp -68
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
addi s1 fp -52
lw s1 0(s1)
lw s2 0(sp)
addi sp sp 4
slt s1 s2 s1
xori s1 s1 1
seqz s1 s1
beqz s1 __label__5
addi sp sp -4
addi s1 fp -62
addi sp sp -4
sw s1 0(sp)
addi s1 fp -68
lw s1 0(s1)
lw s2 0(sp)
addi sp sp 4
addi t0 x0 1
li t1 1
mul t1 s1 t0
add s2 s2 t1
mv s1 s2
lb s1 0(s1)
sw s1 0(sp)
jal ra PrintInt
mv s1 a0
addi sp sp 4
j __label__3
__label__5:
addi sp sp -8
addi s1 fp -62
sw s1 0(sp)
addi s1 fp -52
lw s1 0(s1)
sw s1 4(sp)
jal ra reverse_in_place
mv s1 a0
addi sp sp 8
addi s1 fp -68
addi sp sp -4
sw s1 0(sp)
li s1 0
lw t0 0(sp)
sw s1 0(t0)
addi sp sp 4
j __label__7
__label__6:
addi s1 fp -68
mv s2 s1
lw s1 0(s2)
addi s3 s1 1
sw s3 0(s2)
__label__7:
addi s1 fp -68
lw s1 0(s1)
addi sp sp -4
sw s1 0(sp)
addi s1 fp -52
lw s1 0(s1)
lw s2 0(sp)
addi sp sp 4
slt s1 s2 s1
xori s1 s1 1
seqz s1 s1
beqz s1 __label__8
addi sp sp -4
addi s1 fp -62
addi sp sp -4
sw s1 0(sp)
addi s1 fp -68
lw s1 0(s1)
lw s2 0(sp)
addi sp sp 4
addi t0 x0 1
li t1 1
mul t1 s1 t0
add s2 s2 t1
mv s1 s2
lb s1 0(s1)
sw s1 0(sp)
jal ra PrintInt
mv s1 a0
addi sp sp 4
j __label__6
__label__8:
li s1 0
mv a0 s1
j _main
addi sp sp 20
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
  
