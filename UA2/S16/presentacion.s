	.file	"presentacion.c"
	.text
	.section .rdata,"dr"
	.align 8
.LC0:
	.ascii "=================================================\0"
	.align 8
.LC1:
	.ascii " Instituto Nacional de Aprendizaje\0"
	.align 8
.LC2:
	.ascii " M\303\263dulo: CSTI12010 Dise\303\261o de Algoritmos\0"
	.align 8
.LC3:
	.ascii " Unidad 2: Prograci\303\263n estructurada\0"
.LC4:
	.ascii "\11Sesion 16\0"
	.align 8
.LC5:
	.ascii " Leguaje \"C\" | Compilador: gcc\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC5(%rip), %rax
	movq	%rax, %rcx
	call	puts
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (GNU) 14.4.0"
	.def	puts;	.scl	2;	.type	32;	.endef
