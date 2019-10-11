	addi s0, x0, 5
	addi s1, x0, 10
	add t0, s0, s0
	bne t0, s1, else
	xor s0, x0, x0
	jal x0, exit
else:
	addi s1, s0, -1
exit: