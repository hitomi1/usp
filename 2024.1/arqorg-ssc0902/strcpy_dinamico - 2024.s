# Código que implementa a função strcpy com alocação dinâmica

	.data
	.align 0
	# String a ser copiada
str_src:.asciz "Hello!"
	# Espaço para armazenar o 1o Byte das posições de memória criadas na heap
	.align 2
ptr:	.word

	.text
	.align 2
	.globl main
main:
	# Primeiramente, vamos calcular o tamanho da string de origem e armazenar esse tamanho em t3
	
	# Carrega em t0 o endereço do 1o. Bytes da string de origem
	la t0, str_src
	
	addi t3, zero, 0
	
	# loop para calcular o tamanho
loop_tam:	
	# Lê o caracter armazendo na posição de memória apontada por t0
	lb t2, 0(t0)
	# Incrementa o contador de caracteres
	addi t3, t3, 1
	# Avança o ponteiro na string
	addi t0, t0, 1
	# verifica se chegou no fim da string. Se não chegou, volta no loop
	bne t2, zero, loop_tam
	# Em t3 temos o tamanho da string
	
	# Alocação estática na heap
	# Serviço 9
	# Parâmetro a0: número de Bytes a serem alocados
	# Retorno a0: endereço do 1o Byte alocado
	li a7, 9
	add a0, t3, zero
	ecall
	
	# Coloca o endereco de a0 retornado pela ecall em ptr
	la t4, ptr
	sw a0, 0(t4)
	
	# Coloca em t0 o endereço do 1o Byte da string origem
	la t0, str_src
	
	# Coloca em t1 o endereço do 1o Byte da string alocada na heap
	la t4, ptr
	lw t1, 0(t4)

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
	la t4, ptr
	lw a0, 0(t4)
	ecall
	
	#Encerra o programa
	li a7, 10
	ecall