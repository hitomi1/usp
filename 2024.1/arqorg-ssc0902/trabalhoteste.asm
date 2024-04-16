#Universidade de São Paulo
#Instituto de Ciências Matemáticas e de Computação
#Departamento de Sistemas de Computação
#SSC0902 – Organização e Arquitetura de Computadores
#1ª Trabalho Prático
#Implementação do Jogo "Adivinhe o Número" em Assembly RISC-V

# Membros:
# Breno Goncalves Rodrigues 11734142
# Gustavo Hitomi da Sukva   11801202
# Leandro Sena Silva         9293060

# definindo area de dados
.data

boas_vindas: .asciz "Boas Vindas Ao jogo de Advinhação\n"
instrucoes1: .asciz "O jogo randomicamente inicializara com um número aleatório de 1 a 100.\n"
instrucoes2: .asciz "você deve fornecer seus palpites e o programa ira dar dicas se o número é maior ou menor que fornecido.\n"
instrucoes3: .asciz "Ao final ele exibira seus palpites e quantos palpites deu.\n"
input: .asciz "Digite um número entre 1 e 100\n"
dica_alto: .asciz "Mais Alto\n"
dica_baixo: .asciz "Mais Baixo\n"
parabens: .asciz "Parabéns, você acertou o número!\n"
palpites: .asciz "Seus palpites:\n"
quantidade_palpites: .asciz "Quantos palpites você deu: "
espaco: .asciz " "
parenteses1: .asciz "("
parenteses2: .asciz ")"
pular_linha: .asciz "\n"

# parametros para a funcao de congruencia linear
seed: .word 42      # semente inicial
a: .word 1664525    # multiplicador
c: .word 1013904223 # incremento
m: .word 100 # modulo

# salva o numero gerado
numero_gerado: .word 0

# "struct" para a lista
tamanho_node: .word 8
quantidade_tentativas: .word 0
struct_node: .word 0

.text
.globl main
main:
    call exibir_boas_vindas
    call exibir_instrucoes
    call gerar_numero_aleatorio
    call comparar

# funcao para ler inteiro do teclado 
ler_inteiro:
    li a7, 5
    ecall
    ret

# exibir as boas vindas
exibir_boas_vindas:
    la a0, boas_vindas
    li a7, 4
    ecall
    ret

# exibir instrucoes de jogo
exibir_instrucoes:
    la a0, instrucoes1
    li a7, 4
    ecall
    la a0, instrucoes2
    li a7, 4
    ecall
    la a0, instrucoes3
    li a7, 4
    ecall
    ret

# exibir parenteses (
exibir_parenteses1:
    la a0, parenteses1
    li a7, 4
    ecall
    ret

# exibir parenteses )
exibir_parenteses2:
    la a0, parenteses2
    li a7, 4
    ecall
    ret

# exibir inteiro
exibir_inteiro:
    li a7, 1
    ecall
    ret

# exibir espaço
exibir_espaco:
    la a0, espaco
    li a7, 4
    ecall
    ret

# pular linha
exibir_pular_linha:
    la a0, pular_linha
    li a7, 4
    ecall
    ret

# dar dica alto
exibir_dica_alto:
    la a0, dica_alto
    li a7, 4
    ecall
    j aqui

# dar dica baixo
exibir_dica_baixo:
    la a0, dica_baixo
    li a7, 4
    ecall
    j aqui

# exibir vitoria
exibir_vitoria:
    la a0, parabens
    li a7, 4
    ecall
    call contar_palpites
    call exibir_mensagem_palpites
    call exibir_palpites

# exibir mensagem de palpite 
exibir_mensagem_palpites:
    la a0, palpites
    li a7, 4
    ecall
    ret

# exibir mensagem de quantidade de palpites
exibir_quantidade_palpites:
    la a0, quantidade_palpites
    li a7, 4
    ecall
    ret

# gera um numero aleatorio utilizando do algoritmo de gerador congruente linear
gerar_numero_aleatorio:
    # carrega a semente
    li a7, 30     # código da syscall para obter o tempo do sistema
    ecall         # chamar a syscall
    mv t0, a0     # mover o tempo do sistema para a0 (poderia ser feito de outra maneira)

    # calcula o proximo numero aleatorio usando o gerador congruente linear
    lw t1, a
    mul t0, t0, t1   # multiplica a semente pelo multiplicador
    lw t1, c
    add t0, t0, t1   # adiciona o incremento
    lw t1, m
    rem t0, t0, t1   # calcula o modulo

    # calcula o numero aleatorio entre 1 e 100
    li t1, 100       # carrega 100 em t1
    remu t0, t0, t1   # calcula o modulo em relacao a 100
    addi t0, t0, 1   # adiciona 1 para garantir que o numero aleatorio esta entre 1 e 100

    # salva o numero aleatorio no endereco de numero_gerado
    mv a0, t0
    la t0, numero_gerado
    sw a0, 0(t0)
    ret

# salva em t1 o numero aleatorio gerado
carregar_numero_aleatorio:
    la t0, numero_gerado
    lw t1, 0(t0)
    ret

# cria um novo no para a lista
criar_no:
    lw a0, tamanho_node
    li a7, 9
    ecall
    ret

# chamada para as comparacoes em geral
comparar:
    call ler_inteiro
    mv t2, a0

    call verificar_palpite

contar_palpites:
    la t1, quantidade_tentativas
    lw a0, 0(t1)
    addi a0, a0, 1
    sw a0, 0(t1)
    ret

verificar_palpite:
    call carregar_numero_aleatorio
    #se igual
    beq t2, t1, exibir_vitoria
    # se menor
    blt t2, t1, exibir_dica_alto
    # se maior
    bgt t2, t1, exibir_dica_baixo

aqui:
    call contar_palpites
    call criar_no
    mv t3, a0

    la t0, struct_node
    # beqz t0, lista_vazia
    # encontra o ultimo no da lista
loop_encontrar_ultimo:
        lw t1, 4(t0) # carrega o endereco do proximo no
        beqz t1, fim_loop_encontrar_ultimo # se o proximo no for nulo, sai do loop
        mv t0, t1    # atualiza o ponteiro para o proximo no
        j loop_encontrar_ultimo

fim_loop_encontrar_ultimo:
    # atualiza o proximo ponteiro do ultimo no para apontar para o novo no
    sw t2, 0(t0)
    sw t3, 4(t0)

    call comparar

# lista_vazia:
#     # atualiza o endereco da lista para apontar para o novo no
#     mv t0, t2
#     j loop_encontrar_ultimo
   
# exibe os palpites
exibir_palpites:
    la t0, struct_node
    call loop_exibir_palpites

loop_exibir_palpites:
    # carrega o valor do no atual
    call exibir_parenteses1
    lw a0, 0(t0)
    call exibir_inteiro
    call exibir_parenteses2
    call exibir_espaco

    lw t0, 4(t0) # atualiza o ponteiro para o proximo no
    beq t0, zero, fim_loop_exibir_palpites # se o próximo no for nulo, sai do loop
    j loop_exibir_palpites

fim_loop_exibir_palpites:

    call exibir_pular_linha
    call exibir_quantidade_palpites
    la a0, quantidade_tentativas
    lw a0, 0(a0)
    call exibir_inteiro
    j finalizar_programa
    
# chamada do sistema para encerrar o programa
finalizar_programa:
    li a7, 10
    ecall