alloca:
  addi a0 sp 4
  lw t0 0(sp)
  slli t0 t0 2
  srli t0 t0 2
  sub sp sp t0
  jr ra
