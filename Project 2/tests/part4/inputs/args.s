main:
addi sp sp -4
sw fp 0(sp)
mv fp sp
addi sp sp -48
sw s1 -4(fp)
sw s2 -8(fp)
sw s3 -12(fp)
sw s4 -16(fp)
sw s5 -20(fp)
sw s6 -24(fp)
sw s7 -28(fp)
sw s8 -32(fp)
sw s9 -36(fp)
sw s10 -40(fp)
sw s11 -44(fp)
sw ra -48(fp)
addi sp sp -20
addi s1 x0 3
sw s1 16(sp)
addi s1 x0 5
sw s1 12(sp)
addi s1 x0 4
sw s1 8(sp)
addi s1 x0 2
sw s1 4(sp)
addi s1 x0 10
sw s1 0(sp)
jal ra h
mv s1 a0
addi sp sp 20
mv a0 s1
j _main
_main:
lw s1 -4(fp)
lw s2 -8(fp)
lw s3 -12(fp)
lw s4 -16(fp)
lw s5 -20(fp)
lw s6 -24(fp)
lw s7 -28(fp)
lw s8 -32(fp)
lw s9 -36(fp)
lw s10 -40(fp)
lw s11 -44(fp)
lw ra -48(fp)
mv sp fp
lw fp 0(sp)
addi sp sp 4
mv a1 a0
addi a0 x0 17
ecall
