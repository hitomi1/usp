# CODIGO ASSEMBLY PARA O CALCULO DO FATORIAL NAO RECURSIVO
#
# inteiro positivo n. (Ex: 0! = 1;  3! = 3*2*1 = 6) */
# código em C
#
# #include <stdio.h>
# #include <conio.h>

# int fatorial(int n)
# {
#	int fat = 1;
#	while (n > 1)	{
#		fat = fat * n--;
#   	}
#    	return(fat);
# }
#
# void main()
# {
#  	int n = 0;
#
#  	printf("Digite um numero para o fatorial:");
#   	scanf("%d", &n);
#
#  	printf("O fatorial de %d e' %d\n", n, fatorial(n));
#
#    	return;
# }
#*******************************************************************


	.data		# inicia o segmento de dados
	.align 0	# determina o alinhamento dos bytes (2^0)

str1:
	.asciz "Digite um numero para o fatorial: "
str2:
	.asciz "O fatorial de "
str3:
	.asciz " eh :"

	.text		# inicia o segmento de texto
	.align 2	# determina alinhamento de 2^2, ou seja, 4 bytes
	.globl main	# determina que o identificador main é global

main:

    # Imprimir o string de entrada
    li a7, 4
    la a0, str1
    ecall


    # ler o valor fornecido pelo usuario
    # o valor lido está em a0
    li a7, 5
    ecall

	add s0, a0, zero	# salva o número fornecido pelo usuário em s0

    jal  fatorial		# chama a funcao fatorial
    
	add s1, a1, zero    # salva em s1 o resultado do fatorial

	li a7, 4		# codigo da chamada de sistema que imprime string
	la a0, str2		# string de resposta a ser impressa
	ecall			# chamada do sistema operacional

	li a7, 1		# codigo da chamada de sistema que imprime um inteiro
	add a0, zero, s0# inteiro a ser impresso
	ecall			# chamada do sistema operacional

	li a7, 4		# codigo da chamada de sistema que imprime string
	la a0, str3		# string de resposta a ser impressa
	ecall			# chamada do sistema operacional

	li a7, 1		# codigo da chamada de sistema que imprime um inteiro
	add a0, zero, s1# inteiro a ser impresso
	ecall			# chamada do sistema operacional

	li a7, 10		# codigo da chamada de sistema que sai do programa (exit)
	ecall			# chamada do sistema operacional

#******************************************************************
# aqui termina a funcao main e comeca a funcao fatorial
# Funcao fatorial
# Entrada: a0 = número do fatorial a ser calculado
# Saida: a1 = valor do fatorial calculado
#******************************************************************

fatorial:

	addi a1, zero, 1	# fat=1
	addi t0, zero, 1	# t0 auxilia na parada da repeticao

loopfat:		       	# loop para o calculo do fatorial 
	ble a0, t0, sai_loop# condicional que marca o inicio do while
	mul a1, a1, a0	    # fat = fat * n
    addi a0, a0, -1     # n--
   	j loopfat
sai_loop:

	jr ra			# retorna para a funcao main

	# esta linha nunca sera atingida
