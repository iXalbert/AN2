	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 15, 1
	.globl	_gcd                            ; -- Begin function gcd
	.p2align	2
_gcd:                                   ; @gcd
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	str	w1, [sp, #8]
	b	LBB0_1
LBB0_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #8]
	subs	w8, w8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB0_3
	b	LBB0_2
LBB0_2:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #8]
	str	w8, [sp, #4]
	ldr	w8, [sp, #12]
	ldr	w10, [sp, #8]
	sdiv	w9, w8, w10
	mul	w9, w9, w10
	subs	w8, w8, w9
	str	w8, [sp, #8]
	ldr	w8, [sp, #4]
	str	w8, [sp, #12]
	b	LBB0_1
LBB0_3:
	ldr	w8, [sp, #12]
	subs	w8, w8, #0
	cset	w8, ge
	tbnz	w8, #0, LBB0_5
	b	LBB0_4
LBB0_4:
	ldr	w9, [sp, #12]
	mov	w8, #0                          ; =0x0
	subs	w8, w8, w9
	str	w8, [sp]                        ; 4-byte Folded Spill
	b	LBB0_6
LBB0_5:
	ldr	w8, [sp, #12]
	str	w8, [sp]                        ; 4-byte Folded Spill
	b	LBB0_6
LBB0_6:
	ldr	w0, [sp]                        ; 4-byte Folded Reload
	add	sp, sp, #16
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_lcm                            ; -- Begin function lcm
	.p2align	2
_lcm:                                   ; @lcm
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	w0, [x29, #-12]
	str	w1, [sp, #16]
	ldur	w8, [x29, #-12]
	subs	w8, w8, #0
	cset	w8, eq
	tbnz	w8, #0, LBB1_2
	b	LBB1_1
LBB1_1:
	ldr	w8, [sp, #16]
	subs	w8, w8, #0
	cset	w8, ne
	tbnz	w8, #0, LBB1_3
	b	LBB1_2
LBB1_2:
	stur	xzr, [x29, #-8]
	b	LBB1_4
LBB1_3:
	ldur	w0, [x29, #-12]
	ldr	w1, [sp, #16]
	bl	_gcd
                                        ; implicit-def: $x8
	mov	x8, x0
	sxtw	x8, w8
	str	x8, [sp, #8]
	ldursw	x8, [x29, #-12]
	ldr	x9, [sp, #8]
	sdiv	x8, x8, x9
	ldrsw	x9, [sp, #16]
	mul	x8, x8, x9
	stur	x8, [x29, #-8]
	b	LBB1_4
LBB1_4:
	ldur	x0, [x29, #-8]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_sum_array                      ; -- Begin function sum_array
	.p2align	2
_sum_array:                             ; @sum_array
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #32
	.cfi_def_cfa_offset 32
	str	x0, [sp, #24]
	str	w1, [sp, #20]
	str	wzr, [sp, #16]
	str	wzr, [sp, #12]
	b	LBB2_1
LBB2_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #20]
	subs	w8, w8, w9
	cset	w8, ge
	tbnz	w8, #0, LBB2_4
	b	LBB2_2
LBB2_2:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldr	x8, [sp, #24]
	ldrsw	x9, [sp, #12]
	ldr	w9, [x8, x9, lsl #2]
	ldr	w8, [sp, #16]
	add	w8, w8, w9
	str	w8, [sp, #16]
	b	LBB2_3
LBB2_3:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldr	w8, [sp, #12]
	add	w8, w8, #1
	str	w8, [sp, #12]
	b	LBB2_1
LBB2_4:
	ldr	w0, [sp, #16]
	add	sp, sp, #32
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #112
	stp	x29, x30, [sp, #96]             ; 16-byte Folded Spill
	add	x29, sp, #96
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	stur	x8, [x29, #-8]
	stur	wzr, [x29, #-36]
	mov	w8, #84                         ; =0x54
	stur	w8, [x29, #-40]
	mov	w8, #30                         ; =0x1e
	stur	w8, [x29, #-44]
	ldur	w0, [x29, #-40]
	ldur	w1, [x29, #-44]
	bl	_gcd
	str	w0, [sp, #48]
	ldur	w0, [x29, #-40]
	ldur	w1, [x29, #-44]
	bl	_lcm
	str	x0, [sp, #40]
	adrp	x8, l___const.main.arr@PAGE
	add	x8, x8, l___const.main.arr@PAGEOFF
	ldr	q0, [x8]
	sub	x0, x29, #32
	stur	q0, [x29, #-32]
	ldr	w8, [x8, #16]
	stur	w8, [x29, #-16]
	mov	w1, #5                          ; =0x5
	bl	_sum_array
	str	w0, [sp, #36]
	ldur	w8, [x29, #-40]
                                        ; implicit-def: $x11
	mov	x11, x8
	ldur	w8, [x29, #-44]
                                        ; implicit-def: $x10
	mov	x10, x8
	ldr	w9, [sp, #48]
                                        ; implicit-def: $x8
	mov	x8, x9
	mov	x9, sp
	str	x11, [x9]
	str	x10, [x9, #8]
	str	x8, [x9, #16]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	ldur	w8, [x29, #-40]
                                        ; implicit-def: $x11
	mov	x11, x8
	ldur	w8, [x29, #-44]
                                        ; implicit-def: $x10
	mov	x10, x8
	ldr	x8, [sp, #40]
	mov	x9, sp
	str	x11, [x9]
	str	x10, [x9, #8]
	str	x8, [x9, #16]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	ldr	w9, [sp, #36]
                                        ; implicit-def: $x8
	mov	x8, x9
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	ldur	x9, [x29, #-8]
	adrp	x8, ___stack_chk_guard@GOTPAGE
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
	ldr	x8, [x8]
	subs	x8, x8, x9
	cset	w8, eq
	tbnz	w8, #0, LBB3_2
	b	LBB3_1
LBB3_1:
	bl	___stack_chk_fail
LBB3_2:
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #96]             ; 16-byte Folded Reload
	add	sp, sp, #112
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__const
	.p2align	2, 0x0                          ; @__const.main.arr
l___const.main.arr:
	.long	1                               ; 0x1
	.long	2                               ; 0x2
	.long	3                               ; 0x3
	.long	4                               ; 0x4
	.long	5                               ; 0x5

	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"gcd(%d,%d)=%d\n"

l_.str.1:                               ; @.str.1
	.asciz	"lcm(%d,%d)=%lld\n"

l_.str.2:                               ; @.str.2
	.asciz	"sum=%d\n"

.subsections_via_symbols
