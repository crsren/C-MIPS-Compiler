.data
.text
.globl	f
f:
	sw	$31,-0($sp)
	sw	$30,-4($sp)
	add	$30,$29,$0
	li	$8, 1
	sw	$8,-12($fp)
	beq	$0,$2, else_0
	nop
	li	$8, 11
	sw	$8,-16($fp)
	j	$31
	nop
	b	fi_1
	nop
else_0:
fi_1:
	li	$8, 10
	sw	$8,-16($fp)
	j	$31
	nop
	lw	$31,-0($fp)
	lw	$30,-4($fp)
	add	$29,$30,$0
	j	$31
	nop
