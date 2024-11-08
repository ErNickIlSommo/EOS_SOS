.section .data
v_int: .word 1, 2, 3, 4, 5
n: .word 5
res: .space 4

.section .text
.global _start

_start:
	ldr r0, =v_int	@ load base adrress of the array
	ldr r1, =n		@ load address of n
	ldr r1, [r1]	@ load n value
	ldr r2, =res	@ it'll contain the result
	mov r3, #0		@ index of the array
	mov r4, #1
	bl _prod_array	@ call prodArray function
	
_end:
	b _end

_prod_array:
	cmp r3, r1
	bge _prod_array_done			@ i > n ? exit_to_function : continue
	ldr r5, [r0, r3, lsl #2]		@ load in r4 v[i]
	mul r4, r4, r5					@ r2 *= r4	
	str r4, [r2]					@ store result in res location
	add r3, r3, #1			 		@ i++
	b _prod_array

_prod_array_done:
	bx lr							@ Return from function