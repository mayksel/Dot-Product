section .text
bits 64
default rel
global dotproductasm

dotproductasm:
	mov rax, 0
	loop_start:
		mov rbx, [rdx]
		imul rbx, [r8]
		add rax, rbx

		add rdx, 4
		add r8, 4
		loop loop_start

 
ret