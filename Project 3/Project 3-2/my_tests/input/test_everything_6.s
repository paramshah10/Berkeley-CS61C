	addi s0 x0 5
    add t0 x0 x0
    add t1 x0 x0
loop:
	beq s0 x0 end
 	mul t1 s0 s0
    add t0 t0 t1
    addi s0 s0 -1
  	j loop
  
end:
	add a0 x0 x0