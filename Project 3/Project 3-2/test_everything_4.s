addi    sp, sp, -16
sw      ra, 12(sp)
sw      s0, 8(sp)
addi    s0, sp, 16
sw      a0, -12(s0)
lw      a0, -12(s0)
mul     a0, a0, a0
lw      s0, 8(sp)
lw      ra, 12(sp)
addi    sp, sp, 16