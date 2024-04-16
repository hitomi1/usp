# Lê um valor do teclado
# Imprimir o Hello World ++ <num_digitado> se <num_digitado> >=0
#           Hello World -- <num_digitado>

    .data

	# alinha a memória de dados para definição de caracteres, múltiplos de 1 (2^0)
	.align 0
str1:   .asciz "Hello World ++ ! "
str2:   .asciz "Hello World -- ! "

    .text
	# alinha a parte de código para múltiplo de 4 (2^2)
	.align 2
	
    .globl main

main:
    # Ler um número do teclado
    addi a7, zero, 5	#código para ler inteiro
    ecall

    # salvando o conteúdo lido no registrador s0
    add s0, a0, zero

    # comparar o valor digitado com o valor 0
    # desviar para print_neg se for menor que 0
    blt s0, zero, print_neg
    # o número digitado é >=0

    # imprimir a string
    la a0, str1
    addi a7, zero, 4
    ecall

    j the_end


    # o número digitado é <0
print_neg:
    la a0, str2
    addi a7, zero, 4
    ecall

    # imprimir o numero digitado e encerrar o programa
the_end:
    # imprime o número digitado
    add a0, zero, s0
    addi a7, zero, 1
    ecall

    # encerra o programa
    li a7,10
    ecall
