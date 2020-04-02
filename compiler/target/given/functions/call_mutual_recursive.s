.data
.text
.globl	r1
r1:
	sw	$31,-0($sp)
	sw	$30,-4($sp)
	add	$30,$29,$0
	lw	$2,-8($fp)
	li	$8, 0
	sw	$8,-20($fp)
	lw	$2,-16($fp)
	lw	$3,-24($fp)
	xor	$2,$2,$3
	sltiu	$2,$2,1
	andi	$2,$2,255
	sw	$2,-16($fp)
	beq	$0,$2, else_0
	nop
	li	$8, 1
	sw	$8,-16($fp)
	j	$31
	nop
	b	fi_1
	nop
else_0:
	sub	$29,$29,$16
	lw	$2,-8($fp)
	li	$8, 1
	sw	$8,-20($fp)
	lw	$2,-16($fp)
	lw	$3,-24($fp)
	subu	$2,$2,$3
	sw	$2,-16($fp)
	sw	$2,-8($sp)
	sub	$29,$29,$20
	lw	$2,-8($fp)
	li	$8, 1
	sw	$8,-24($fp)
	lw	$2,-20($fp)
	lw	$3,-28($fp)
	subu	$2,$2,$3
	sw	$2,-20($fp)
	sw	$2,-8($sp)
	lw	$2,-16($fp)
	lw	$3,-20($fp)
	addu	$2,$2,$3
	sw	$2,-16($fp)
	j	$31
	nop
fi_1:
	lw	$31,-0($fp)
	lw	$30,-4($fp)
	add	$29,$30,$0
	j	$31
	nop
