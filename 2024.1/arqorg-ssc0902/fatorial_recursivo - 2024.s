# CODIGO ASSEMBLY PARA O CALCULO DO FATORIAL NAO RECURSIVO
#
# inteiro positivo n. (Ex: 0! = 1;  3! = 3*2*1 = 6) */
# código em C
#
# #include <stdio.h>
# #include <conio.h>

# int fatorial(int n)
# {
#	if (n==0)
#		return (1);
#	return (fatorial(n-1)*n);
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

    # salvar o conteúdo do valor digitado pelo usuário em s0
    add s0, a0, zero

    # chama a função fatorial, 
    # número: a0
    # retorno: a1
    jal fatorial

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
	add a0, zero, a1# inteiro a ser impresso
	ecall			# chamada do sistema operacional

	li a7, 10		# codigo da chamada de sistema que sai do programa (exit)
	ecall			# chamada do sistema operacional



fatorial:
    # reserva espaço na pilha para 2 palavras
    addi sp, sp, -8

    # armazena o conteúdo de a0 e ra 
    sw a0, 0(sp)   
    sw ra, 4(sp)

    # compara o n com 0. Se for igual, é a condição de parada da recursão
    beq a0, zero, retorna_1
	
	# n é diferente de 0
	# atualiza o valor de n
	addi a0, a0, -1
	
	# chama recursivamente a função fatorial
	jal fatorial

    # desempilha o valor de a0
    lw a0, 0(sp)
    # multiplica a0 por a1 e salva em a1
    mul a1, a1, a0
	
	# desvia para sai_fat
	j sai_fat

retorna_1:
	# coloca o valor 1 no registrador de retorno (a1)
	addi a1, zero, 1	
	
sai_fat:
	# desempilha o valor do ra
	lw ra, 4(sp)
	
	# desaloca o espaço da pilha
	addi sp, sp, 8
	
	# retorna para a função que chamou
	jr ra
