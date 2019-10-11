	addi s1, x0, 0
loop:
	beq s0, x0, exit
	add s1, s1, s0
	addi s0, s0, -1
	jal x0, loop
exit: