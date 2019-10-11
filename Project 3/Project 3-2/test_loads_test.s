li t0 1
li t1 -2
addi t2 t2 200
sw t0 0(t2)
sw t1 4(t2)

lw t0 4(t2)	#t0 = -2
lw t1 0(t2)	#t1 = 1

beq t0 t1 bad_loop
bltu t0 t1 bad_loop
blt t1 t0 bad_loop

bne t1 t0 end

bad_loop:
	add x0 x0 x0
	beq x0 x0 bad_loop

end:
	xori s0 s0 4
	sw s0 0(t2)
	lw t0 0(t2)
	beq t0 s0 endend

endend:
	li t0 456
	li t1 864
	vaddh s0 t0 t1
	beq s0 x0 bad_loop
	mul t0 s0 t1
	mulhu t1 s0 t1
	beq t0 t1 bad_loop
	mulh t0 t0 t1
	jal ra func
	li t1 1
	beq t0 t1 theEnd	

func:
	li s1 987
	lb t0 0(s1)

theEnd:
	add x0 x0 x0