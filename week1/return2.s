    .file	"return2.c"
    .text
    .section	.text.startup,"ax",@progbits
    .p2align 4
    .globl	main
    .type	main, @function
main:
    endbr64
    movl	$2, %eax
    ret
    .size	main, .-main
    .ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
    .section	.note.GNU-stack,"",@progbits
    .section	.note.gnu.property,"a"
    .align 8
    .long	1f - 0f
    .long	4f - 1f
    .long	5
0:
    .string	"GNU"
1:
    .align 8
    .long	0xc0000002
    .long	3f - 2f
2:
    .long	0x3
3:
    .align 8
4:
