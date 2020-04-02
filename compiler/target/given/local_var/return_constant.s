.data
.text
.globl	f
f:
	sw	$31,-0($sp)
	sw	$30,-4($sp)
	add	$30,$29,$0
	li	$8, 5678
	sw	$8,-12($fp)
	j	$31
	nop
	lw	$31,-0($fp)
	lw	$30,-4($fp)
	add	$29,$30,$0
	j	$31
	nop
