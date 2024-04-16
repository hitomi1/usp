	.data	# diretiva p/ in�cio do seg de dados
	
	# exemplo de defini��o de um valor inteiro

	
	# defini��o da string
	.align 0
	string:		.asciz "Hello World"

	.text 		# diretiva p/ in�cio do segmento de texto

	.globl main	# diretiva p/ usar rotulo em outro prog.

main:					
	.align 2	# alinha a mem�ria para armazenar as instru��es de 32 bits
	
	addi a7, x0, 4 	# C�digo do servi�o 4 (impress�o de string)
	la a0, string	# Carrega o endere�o do 1o byte de "string" em a0
	ecall			# Chamada ao sistema para impress�o da string

	addi a7, x0, 10	# C�digo do servi�o que encerra
	ecall
