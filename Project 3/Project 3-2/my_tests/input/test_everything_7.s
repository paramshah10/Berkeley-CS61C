	li t0 -1
	li t1 -1
	li t2 -1

	beq t0 t0 start

bad_loop:
	add x0 x0 x0
	beq x0 x0 bad_loop

start:
	slt t2 t0 t1
	bne t2 x0 bad_loop
	addi t2 x0 1
	addi t1 x0 1
	addi t0 x0 4
	slli t2 t2 4
	sll t1 t1 t0
	bne t1 t2 bad_loop
	beq t1 t2 end
	beq x0 x0 bad_loop
end:
	and t0 t1 t2
	andi t0 t0 1
	bltu t0 t2 endend
	beq x0 x0 bad_loop

endend:
	lui t0 4567
	beq t0 x0 bad_loop