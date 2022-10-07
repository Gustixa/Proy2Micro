	.file	"Code.cpp"
	.text
	.globl	mutexCar
	.bss
	.align 8
mutexCar:
	.space 8
	.globl	condFillingGasStation
	.align 8
condFillingGasStation:
	.space 8
	.globl	barrierGasStations
	.align 8
barrierGasStations:
	.space 8
	.globl	amountGasToFill
	.data
	.align 4
amountGasToFill:
	.long	10000
	.globl	gasPerGasStation
	.align 4
gasPerGasStation:
	.long	2000
	.globl	data
	.bss
	.align 8
data:
	.space 8
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "Failed to create the thread.\0"
	.align 8
.LC1:
	.ascii "Failed to join the current thread, to the main thread.\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB947:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$72, %rsp
	.seh_stackalloc	72
	leaq	64(%rsp), %rbp
	.seh_setframe	%rbp, 64
	.seh_endprologue
	movl	%ecx, 64(%rbp)
	movq	%rdx, 72(%rbp)
	call	__main
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -16(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r12
	movl	$0, %r13d
	movslq	%eax, %rdx
	movq	%rdx, %rsi
	movl	$0, %edi
	cltq
	salq	$3, %rax
	addq	$15, %rax
	shrq	$4, %rax
	salq	$4, %rax
	call	___chkstk_ms
	subq	%rax, %rsp
	leaq	32(%rsp), %rax
	addq	$7, %rax
	shrq	$3, %rax
	salq	$3, %rax
	movq	%rax, -24(%rbp)
	movl	$0, %edx
	leaq	mutexCar(%rip), %rax
	movq	%rax, %rcx
	call	pthread_mutex_init
	movl	$0, %edx
	leaq	condFillingGasStation(%rip), %rax
	movq	%rax, %rcx
	call	pthread_cond_init
	movl	-8(%rbp), %eax
	movl	%eax, %r8d
	movl	$0, %edx
	leaq	barrierGasStations(%rip), %rax
	movq	%rax, %rcx
	call	pthread_barrier_init
	movl	$0, -4(%rbp)
	jmp	.L2
.L4:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, %r9d
	leaq	_Z10gasStationPv(%rip), %r8
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_create
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L3
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	perror
.L3:
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L4
	movl	$0, -4(%rbp)
	jmp	.L5
.L7:
	movq	-24(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movq	(%rax,%rdx,8), %rax
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_join
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L6
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	perror
.L6:
	addl	$1, -4(%rbp)
.L5:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L7
	leaq	condFillingGasStation(%rip), %rax
	movq	%rax, %rcx
	call	pthread_cond_destroy
	leaq	mutexCar(%rip), %rax
	movq	%rax, %rcx
	call	pthread_mutex_destroy
	movl	$0, %eax
	movq	%rbx, %rsp
	leaq	8(%rbp), %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%r13
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC2:
	.ascii "Failed to create the thread\0"
	.text
	.globl	_Z10gasStationPv
	.def	_Z10gasStationPv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z10gasStationPv
_Z10gasStationPv:
.LFB948:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$72, %rsp
	.seh_stackalloc	72
	leaq	64(%rsp), %rbp
	.seh_setframe	%rbp, 64
	.seh_endprologue
	movq	%rcx, 64(%rbp)
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	$0, %ecx
	call	time
	movl	%eax, %ecx
	call	srand
	call	rand
	movslq	%eax, %rdx
	imulq	$1374389535, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$6, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	movl	%edx, -8(%rbp)
	movl	-8(%rbp), %edx
	imull	$200, %edx, %edx
	subl	%edx, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -16(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r12
	movl	$0, %r13d
	movslq	%eax, %rdx
	movq	%rdx, %rsi
	movl	$0, %edi
	cltq
	salq	$3, %rax
	addq	$15, %rax
	shrq	$4, %rax
	salq	$4, %rax
	call	___chkstk_ms
	subq	%rax, %rsp
	leaq	32(%rsp), %rax
	addq	$7, %rax
	shrq	$3, %rax
	salq	$3, %rax
	movq	%rax, -24(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L10
.L12:
	movl	-4(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, %r9d
	leaq	_Z8gasPricePv(%rip), %r8
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_create
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L11
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	perror
.L11:
	addl	$1, -4(%rbp)
.L10:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L12
	movl	$0, -4(%rbp)
	jmp	.L13
.L14:
	movq	-24(%rbp), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	movq	(%rax,%rdx,8), %rax
	movl	$0, %edx
	movq	%rax, %rcx
	call	pthread_join
	testl	%eax, %eax
	addl	$1, -4(%rbp)
.L13:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L14
	movq	%rbx, %rsp
	nop
	leaq	8(%rbp), %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%r12
	popq	%r13
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z8gasPricePv
	.def	_Z8gasPricePv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z8gasPricePv
_Z8gasPricePv:
.LFB949:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	$0, %ecx
	call	time
	movl	%eax, %ecx
	call	srand
	call	rand
	movslq	%eax, %rdx
	imulq	$458129845, %rdx, %rdx
	shrq	$32, %rdx
	sarl	$6, %edx
	movl	%eax, %ecx
	sarl	$31, %ecx
	subl	%ecx, %edx
	movl	%edx, -4(%rbp)
	movl	-4(%rbp), %edx
	imull	$600, %edx, %edx
	subl	%edx, %eax
	movl	%eax, -4(%rbp)
	leaq	mutexCar(%rip), %rax
	movq	%rax, %rcx
	call	pthread_mutex_lock
	leaq	mutexCar(%rip), %rax
	movq	%rax, %rcx
	call	pthread_mutex_unlock
	nop
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	_Z7fillGasPv
	.def	_Z7fillGasPv;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z7fillGasPv
_Z7fillGasPv:
.LFB950:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (GNU) 11.3.0"
	.def	pthread_mutex_init;	.scl	2;	.type	32;	.endef
	.def	pthread_cond_init;	.scl	2;	.type	32;	.endef
	.def	pthread_barrier_init;	.scl	2;	.type	32;	.endef
	.def	pthread_create;	.scl	2;	.type	32;	.endef
	.def	perror;	.scl	2;	.type	32;	.endef
	.def	pthread_join;	.scl	2;	.type	32;	.endef
	.def	pthread_cond_destroy;	.scl	2;	.type	32;	.endef
	.def	pthread_mutex_destroy;	.scl	2;	.type	32;	.endef
	.def	time;	.scl	2;	.type	32;	.endef
	.def	srand;	.scl	2;	.type	32;	.endef
	.def	rand;	.scl	2;	.type	32;	.endef
	.def	pthread_mutex_lock;	.scl	2;	.type	32;	.endef
	.def	pthread_mutex_unlock;	.scl	2;	.type	32;	.endef
