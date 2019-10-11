error_and_exit:
  li a1 1
  li a0 17
  ecall
  mv a0 x0
  jr ra

exit:
  li a1 0
  li a0 17
  ecall
  mv a0 x0
  jr ra
