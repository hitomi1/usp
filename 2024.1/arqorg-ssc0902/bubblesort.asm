.data
	.align 2
vet:	.word	1, 2, 5, 0, -1

	.text
	.globl main
main :
	li s7, 4		# n-1 in s7 
	la s0, vet 		# s0 contains the vector
	
	addi t0, t0, 1	# flag

loop0:
	beqz t0, final		#if (flag == 0) end
	mv t0,zero		# flag = 0
	mv t3, s7
	
loop1: #run in the vector
	beq t3,zero,end_loop1 #while not the end of the vec
	lw t1, 0(s0) 		#a[i]		
	lw t2, 4(s0)		#a[i+1]

	ble t2,t1,swap	#go to swap function
swapback:
	addi s0,s0, 4		#go to the next value of the vec
	addi t3,t3,-1		
	
	j loop1

end_loop1:
	addi  s0, s0, -16 #go back to the first position of the vec
	j loop0

swap:
	sw t1, 4(s0) #a[i+1] = a[i]
	sw t2, 0(s0) #a[i] = a[i+1]

	addi t0, zero, 1 #flag = 1

	j swapback

final:
	addi t0,t0,5
print:
	
	beq t0,zero,end #run the vector
	addi t0,t0,-1
	lw a0,0(s0) #print each element
	li a7,1
	ecall
	addi s0,s0,4
	
	j print
	
end:

	li a7, 10 #exit
	ecall