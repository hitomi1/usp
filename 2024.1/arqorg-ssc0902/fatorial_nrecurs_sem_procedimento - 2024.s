# CODIGO ASSEMBLY PARA O CALCULO DO FATORIAL NAO RECURSIVO
#
#void main()  {
#int n, fat, count;
#
#   n = 1;
#
#   printf("Digite um numero para o fatorial:");
#   scanf("%d", &n);
#
#   fat = 1;
#   count = n;
#   while (count > 1)	{
#	fat = fat * count--;
#   }
#
#   printf("O fatorial de %d eh: %d", n, fat);
#   getch();
#
#}
#
#
	.data		# inicia o segmento de dados
	.align 0	# determina o alinhamento dos bytes (2 elevado a 0)
str1:
	.asciz "Digite um numero para o fatorial: "
str2:
	.asciz "O fatorial de "
str3:
	.asciz " eh :"


	.text		# inicia o segmento de texto
	.align 2	# determina alinhamento de 2 elevado a 2, ou seja, 4 bytes
	.globl main	# determina que o identificador main é global

main:
	li a7, 4		# codigo da chamada de sistema que imprime string
	la a0, str1		# string a ser impressa
	ecall			# chamada do sistema operacional

	li a7, 5		# codigo da chamada de sistema que le um inteiro
	ecall			# chamada do sistema operacional

	add s0, a0, zero	# salva o valor inteiro lido em s0  (eh o valor de n)
	
	addi s1, zero, 1	# atribui 1 ao registrador s1  (fat = 1)
	add s2, zero, s0 	# copia o valor de n para não perder o valor digitado pelo usuario
	addi t0, zero, 1	# atribui 1 ao registrador t0. Usado na repeticao como parada

loopfat:			# loop para o calculo do fatorial 
	ble s2, t0, sai_loop   # condicional que marca o inicio do while

	mul s1, s1, s2	# fat = fat * count
    addi s2, s2, -1	# count--
   	j loopfat

sai_loop:
	# impressao do resultado

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
