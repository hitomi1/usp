# Código que implementa a função strcpy com alocação estática

	.data
	.align 0
	# String a ser copiada
str_src:.asciz "Hello!"
	# Espaço para cópia
str_dst:.space 7

	.text
	.align 2
	.globl main
main:
	# Carrega em t0 e t1 os endereços dos 1os. Bytes das duas strings	
	la t0, str_src
	la t1, str_dst

	# Lê o conteúdo da posição de memória apontada por t0 e coloca em t2
	lb t2,0(t0)
	# Escreve o conteúdo de t2 na posição de memória apontada por t1
	sb t2,0(t1)
loop:
	# Se o valor em t2 é igual a 0, sai do loop
	beq t2,zero, sai_loop

	# Avança os ponteiros das duas strings
	addi t0,t0,1
	addi t1,t1,1
	
	# Lê o conteúdo da posição de memória apontada po t0 e coloca em t2
	lb t2,0(t0)
	# Escreve o conteúdo de t2 na posição de memória apontada por t1
	sb t2,0(t1)
	# Volta incondicionalmente para o teste
	j loop

sai_loop:
	# imprime a string copiada
	li a7, 4
	la a0, str_dst
	ecall
	
	#Encerra o programa
	li a7, 10
	ecall
