; MULTIBOOT header
MBALIGN  equ  1 << 0            
MEMINFO  equ  1 << 1            
FLAGS    equ  MBALIGN | MEMINFO 
MAGIC    equ  0x1BADB002        
CHECKSUM equ -(MAGIC + FLAGS)   
 
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 16
resb 16384

section .text
global _start
_start:
	extern _stack_top
	mov esp, _stack_top
	extern kernel_main
	call kernel_main
	jmp $
.end:
