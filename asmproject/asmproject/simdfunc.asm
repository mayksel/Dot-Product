section .text
bits 64
default rel
global dotproductsimd

dotproductsimd:


	shr rcx, 3
	mov rax, 0 

	L1:
		vmovdqu ymm0, [rdx]
		vmovdqu ymm1, [r8] 

		vpmulld ymm2, ymm1, ymm0 
		vphaddd ymm3, ymm2,ymm2 

		vextractf128 xmm4,ymm3,0 
		vpextrd rbx, xmm4, 0 
		add rax, rbx
		vpextrd rbx, xmm4, 1
		add rax, rbx

		vextractf128 xmm4,ymm3,1 
		vpextrd rbx, xmm4, 0
		add rax, rbx
		vpextrd rbx, xmm4, 1
		add rax, rbx
		

		add rdx, 32 
		add r8, 32 

		loop L1

	ret