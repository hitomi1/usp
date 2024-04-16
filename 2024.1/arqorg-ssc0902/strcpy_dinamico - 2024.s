# C�digo que implementa a fun��o strcpy com aloca��o din�mica

	.data
	.align 0
	# String a ser copiada
str_src:.asciz "Hello!"
	# Espa�o para armazenar o 1o Byte das posi��es de mem�ria criadas na heap
	.align 2
ptr:	.word

	.text
	.align 2
	.globl main
main:
	# Primeiramente, vamos calcular o tamanho da string de origem e armazenar esse tamanho em t3
	
	# Carrega em t0 o endere�o do 1o. Bytes da string de origem
	la t0, str_src
	
	addi t3, zero, 0
	
	# loop para calcular o tamanho
loop_tam:	
	# L� o caracter armazendo na posi��o de mem�ria apontada por t0
	lb t2, 0(t0)
	# Incrementa o contador de caracteres
	addi t3, t3, 1
	# Avan�a o ponteiro na string
	addi t0, t0, 1
	# verifica se chegou no fim da string. Se n�o chegou, volta no loop
	bne t2, zero, loop_tam
	# Em t3 temos o tamanho da string
	
	# Aloca��o est�tica na heap
	# Servi�o 9
	# Par�metro a0: n�mero de Bytes a serem alocados
	# Retorno a0: endere�o do 1o Byte alocado
	li a7, 9
	add a0, t3, zero
	ecall
	
	# Coloca o endereco de a0 retornado pela ecall em ptr
	la t4, ptr
	sw a0, 0(t4)
	
	# Coloca em t0 o endere�o do 1o Byte da string origem
	la t0, str_src
	
	# Coloca em t1 o endere�o do 1o Byte da string alocada na heap
	la t4, ptr
	lw t1, 0(t4)

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
	la t4, ptr
	lw a0, 0(t4)
	ecall
	
	#Encerra o programa
	li a7, 10
	ecall