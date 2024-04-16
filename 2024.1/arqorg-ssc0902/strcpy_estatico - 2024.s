# C�digo que implementa a fun��o strcpy com aloca��o est�tica

	.data
	.align 0
	# String a ser copiada
str_src:.asciz "Hello!"
	# Espa�o para c�pia
str_dst:.space 7

	.text
	.align 2
	.globl main
main:
	# Carrega em t0 e t1 os endere�os dos 1os. Bytes das duas strings	
	la t0, str_src
	la t1, str_dst

	# L� o conte�do da posi��o de mem�ria apontada por t0 e coloca em t2
	lb t2,0(t0)
	# Escreve o conte�do de t2 na posi��o de mem�ria apontada por t1
	sb t2,0(t1)
loop:
	# Se o valor em t2 � igual a 0, sai do loop
	beq t2,zero, sai_loop

	# Avan�a os ponteiros das duas strings
	addi t0,t0,1
	addi t1,t1,1
	
	# L� o conte�do da posi��o de mem�ria apontada po t0 e coloca em t2
	lb t2,0(t0)
	# Escreve o conte�do de t2 na posi��o de mem�ria apontada por t1
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
