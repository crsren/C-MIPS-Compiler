.data
.text
.globl	f
f:
	sw	$31,-0($sp)
	sw	$30,-4($sp)
	add	$30,$29,$0
	li	$8, 10
	sw	$8,-16($fp)
	sw	$2,-8($fp)
	li	$8, 20
	sw	$8,-24($fp)
	lw	$2,-8($fp)
	lw	$2,-28($fp)
	lw	$3,-32($fp)
	addu	$2,$2,$3
	sw	$2,-28($fp)
	sw	$2,-16($fp)
	lw	$2,-16($fp)
	j	$31
	nop
	lw	$31,-0($fp)
	lw	$30,-4($fp)
	add	$29,$30,$0
	j	$31
	nop
