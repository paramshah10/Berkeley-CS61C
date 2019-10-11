li ??? 0 # Replace ??? with your register choice from part 1
li s1 0
jal LogAnd
jal PrintRes

li ??? 4 # Replace ??? with your register choice from part 1
li s1 0
jal LogAnd
jal PrintRes

li ??? 0 # Replace ??? with your register choice from part 1
li s1 -1
jal LogAnd
jal PrintRes

li ??? 2 # Replace ??? with your register choice from part 1
li s1 1
jal LogAnd
jal PrintRes

li ??? 2 # Replace ??? with your register choice from part 1
li s1 2
jal LogAnd
jal PrintRes

li ??? 12 # Replace ??? with your register choice from part 1
li s1 9
jal LogAnd
jal PrintRes

jal Exit

LogAnd:
  # Place your Code here for logical and. Remember this is NOT a function call
  # You should perform all of your operations on the s1 and ??? register. You
  # should also assume that these are the only two values to operate on
  # (no nested expressions)


  # End of your code
  jr ra

PrintRes:
  mv a1 s1
  li a0 1
  ecall
  jr ra

Exit:
  li a0 10
  ecall
