.data
.text
.globl	g
g:
	sw	$31,-0($sp)
	sw	$30,-4($sp)
	add	$30,$29,$0
	lw	$2,-8($fp)
	lw	$2,-12($fp)
	lw	$2,-32($fp)
	lw	$3,-36($fp)
	addu	$2,$2,$3
	sw	$2,-32($fp)
	lw	$2,-16($fp)
	lw	$2,-32($fp)
	lw	$3,-36($fp)
	addu	$2,$2,$3
	sw	$2,-32($fp)
	lw	$2,-20($fp)
	lw	$2,-32($fp)
	lw	$3,-36($fp)
	addu	$2,$2,$3
	sw	$2,-32($fp)
	lw	$2,-24($fp)
	lw	$2,-32($fp)
	lw	$3,-36($fp)
	addu	$2,$2,$3
	sw	$2,-32($fp)
	j	$31
	nop
	lw	$31,-0($fp)
	lw	$30,-4($fp)
	add	$29,$30,$0
	j	$31
	nop
.text
.globl	f
f:
	sw	$31,-0($sp)
	sw	$30,-4($sp)
	add	$30,$29,$0
	sub	$29,$29,$8
	li	$8, 1
	sw	$8,-12($fp)
	sw	$2,-8($sp)
	li	$8, 2
	sw	$8,-16($fp)
	sw	$2,-12($sp)
	li	$8, 3
	sw	$8,-20($fp)
	sw	$2,-16($sp)
	li	$8, 4
	sw	$8,-24($fp)
	sw	$2,-20($sp)
	li	$8, 5
	sw	$8,-28($fp)
	sw	$2,-24($sp)
	j	$31
	nop
	lw	$31,-0($fp)
	lw	$30,-4($fp)
	add	$29,$30,$0
	j	$31
	nop
