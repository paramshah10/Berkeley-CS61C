Func: 
	addi t0 x0 1
Loop: 
	and t1 a1 a1
	beq t1 x0 Done
	mul t0 t0 a0
	addi a1 a1 -1
	jal x0 Loop
Done: 
	add a0 t0 x0