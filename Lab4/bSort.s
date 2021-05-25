	.file	"bSort.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	bSort
	.type	bSort, @function
bSort:
	addiw	a7,a1,-1
	ble	a7,zero,.L1
	mv	t1,a7
	slli	t3,a7,2
	add	t3,a0,t3
	slli	a6,a1,2
	add	a6,a0,a6
	li	a0,0
	addi	a6,a6,-8
	addiw	a1,a1,-2
	j	.L3
.L4:
	addi	a5,a5,-4
	beq	a5,a2,.L7
.L5:
	lw	a4,-4(a5)
	lw	a3,0(a5)
	ble	a4,a3,.L4
	sw	a3,-4(a5)
	sw	a4,0(a5)
	j	.L4
.L7:
	addiw	a0,a0,1
	beq	a0,t1,.L1
.L3:
	ble	a7,a0,.L7
	subw	a2,a1,a0
	slli	a5,a2,32
	srli	a2,a5,30
	sub	a2,a6,a2
	mv	a5,t3
	j	.L5
.L1:
	ret
	.size	bSort, .-bSort
	.ident	"GCC: (SiFive GCC-Metal 10.2.0-2020.12.8) 10.2.0"
