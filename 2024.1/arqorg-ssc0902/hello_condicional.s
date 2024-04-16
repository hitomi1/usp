# L� um valor do teclado
# Imprimir o Hello World ++ <num_digitado> se <num_digitado> >=0
#           Hello World -- <num_digitado>

    .data

	# alinha a mem�ria de dados para defini��o de caracteres, m�ltiplos de 1 (2^0)
	.align 0
str1:   .asciz "Hello World ++ ! "
str2:   .asciz "Hello World -- ! "

    .text
	# alinha a parte de c�digo para m�ltiplo de 4 (2^2)
	.align 2
	
    .globl main

main:
    # Ler um n�mero do teclado
    addi a7, zero, 5	#c�digo para ler inteiro
    ecall

    # salvando o conte�do lido no registrador s0
    add s0, a0, zero

    # comparar o valor digitado com o valor 0
    # desviar para print_neg se for menor que 0
    blt s0, zero, print_neg
    # o n�mero digitado � >=0

    # imprimir a string
    la a0, str1
    addi a7, zero, 4
    ecall

    j the_end


    # o n�mero digitado � <0
print_neg:
    la a0, str2
    addi a7, zero, 4
    ecall

    # imprimir o numero digitado e encerrar o programa
the_end:
    # imprime o n�mero digitado
    add a0, zero, s0
    addi a7, zero, 1
    ecall

    # encerra o programa
    li a7,10
    ecall
