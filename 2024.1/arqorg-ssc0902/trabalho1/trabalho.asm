# Universidade de São Paulo
# Instituto de Ciências Matemáticas e de Computação
# Departamento de Sistemas de Computação
# SSC0902 – Organização e Arquitetura de Computadores
# 1ª Trabalho Prático
# Implementação do Jogo "Adivinhe o Número" em Assembly RISC-V

# Membros:
# Breno Goncalves Rodrigues 11734142
# Gustavo Hitomi da Silva   11801202
# Leandro Sena Silva         9293060

# Definição da área de dados
.data
boas_vindas: .asciz "Boas Vindas Ao jogo de Advinhação\n"
instrucoes1: .asciz "O jogo randomicamente inicializara com um número aleatório de 1 a 100.\n"
instrucoes2: .asciz "Você deve fornecer seus palpites e o programa irá dar dicas se o número é maior ou menor que fornecido.\n"
instrucoes3: .asciz "Ao final ele mostrará seus palpites e quantos palpites deu.\n"
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

# Parâmetros para a função de congruência linear
seed: .word 42 # Semente inicial
a: .word 1664525 # Multiplicador
c: .word 1013904223 # Incremento
m: .word 100 # Módulo

# Número gerado pelo gerador congruente linear
numero_gerado: .word 0

# Quantidade de tentativas
quantidade_tentativas: .word 0

# Estrutura de dados para a lista encadeada
tamanho_node: .word 8
struct_node: .word 0

# Definição da área de texto
.text
.globl main
main:
    call exibir_boas_vindas
    call exibir_instrucoes
    call gerar_numero_aleatorio
    call comparar

# Função para ler inteiro do teclado 
ler_inteiro:
    li a7, 5
    ecall
    ret

# Mostrar as boas-vindas
exibir_boas_vindas:
    la a0, boas_vindas
    li a7, 4
    ecall
    ret

# Mostrar instruções do jogo
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

# Exibir "("
exibir_parenteses1:
    la a0, parenteses1
    li a7, 4
    ecall
    ret

# Exibir ")"
exibir_parenteses2:
    la a0, parenteses2
    li a7, 4
    ecall
    ret

# Exibir número inteiro
exibir_inteiro:
    li a7, 1
    ecall
    ret

# Exibir caractere espaço
exibir_espaco:
    la a0, espaco
    li a7, 4
    ecall
    ret

# Pular linha
exibir_pular_linha:
    la a0, pular_linha
    li a7, 4
    ecall
    ret

# Dar dica "mais alto"
exibir_dica_alto:
    la a0, dica_alto
    li a7, 4
    ecall
    j comparar

# Dar dica "mais baixo"
exibir_dica_baixo:
    la a0, dica_baixo
    li a7, 4
    ecall
    j comparar

# Mostrar mensagem de vitória
exibir_vitoria:
    la a0, parabens
    li a7, 4
    ecall

    call exibir_palpites

    call ler_inteiro
    li t0, 0

    beq a0, t0, finalizar_programa

# Incrementar a quantidade de tentativas
contar_palpites:
    la t1, quantidade_tentativas
    lw a0, 0(t1)
    addi a0, a0, 1
    sw a0, 0(t1)
    ret

# Gerar um número aleatório usando o algoritmo de gerador congruente linear
gerar_numero_aleatorio:
    # Carregar a semente
    li a7, 30
    ecall
    
    mv t0, a0

    # Calcular o próximo número aleatório usando o gerador congruente linear
    la t5, a
    lw t1, 0(t5)
    mul t0, t0, t1   # Multiplica a semente pelo multiplicador
    la t5, c
    lw t1, 0(t5)
    add t0, t0, t1   # Adiciona o incremento
    la t5, m
    lw t1, 0(t5)
    remu t0, t0, t1   # Calcula o módulo

    # Calcular o número aleatório entre 1 e 100
    li t1, 100       # Carregar 100 em t1
    rem t0, t0, t1   # Calcular o módulo em relação a 100
    addi t0, t0, 1   # Adicionar 1 para garantir que o número aleatório esteja entre 1 e 100

    # Atualizar a semente para o próximo uso
    la t1, seed      # Carregar o endereço de seed em t1
    sw t0, 0(t1)     # Armazenar o valor de t0 no endereço de memória de seed

    # Salvar o número aleatório no endereço de numero_gerado
    mv a0, t0
    la t0, numero_gerado
    sw a0, 0(t0)
    ret

# Carregar em t1 o número aleatório gerado
carregar_numero_aleatorio:
    la t0, numero_gerado
    lw t1, 0(t0)
    ret

# Criar um nó na lista encadeada
criar_no:
    li a0, 8
    li a7, 9
    ecall
    ret

# Comparar o palpite com o número gerado
comparar:
    call ler_inteiro
    mv t2, a0

    call inserir_lista

inserir_lista:
    call contar_palpites
    call criar_no
    mv t3, a0

    la t0, struct_node
    lw t5, 0(t0)
    
    beqz t5, lista_vazia
    # Encontrar o último nó da lista
    loop_encontrar_ultimo:
        lw t1, 4(t0) # Carregar o endereço do próximo nó
        beqz t1, fim_loop_encontrar_ultimo # Se o próximo nó for nulo, sair do loop
        mv t0, t1    # Atualizar o ponteiro para o próximo nó
        j loop_encontrar_ultimo

    fim_loop_encontrar_ultimo:
    
    # Atualizar o próximo ponteiro do último nó para apontar para o novo nó
    sw t2, 0(t0)
    sw t3, 4(t0)
    
    li t5, -1
    sw t5, 0(t3)
    
    call carregar_numero_aleatorio
    # Se igual
    beq t2, t1, exibir_vitoria
    # Se menor
    blt t2, t1, exibir_dica_alto
    # Se maior
    bgt t2, t1, exibir_dica_baixo
    
    j fim_adicionar_palpite


lista_vazia:
    # Atualizar o endereço da lista para apontar para o novo nó
    sw t3, 0(t0)
    j loop_encontrar_ultimo
   
fim_adicionar_palpite:
    call comparar

exibir_palpites:
    la t0, struct_node # Carregar o endereço da lista

# Exibir os palpites
loop_exibir_palpites:
    # Carregar o valor do nó atual
    beqz t0, fim_loop_exibir_palpites # Se o próximo nó for nulo, sair do loop
    lw t5, 0(t0)
    li t6, -1
    beq t5, t6, fim_loop_exibir_palpites
    call exibir_parenteses1
    lw a0, 0(t0)
    call exibir_inteiro
    call exibir_parenteses2
    call exibir_espaco

    lw t0, 4(t0) # Atualizar o ponteiro para o próximo nó
    # beqz t0, fim_loop_exibir_palpites # Se o próximo nó for nulo, sair do loop
    j loop_exibir_palpites

fim_loop_exibir_palpites:
    call exibir_pular_linha
    call exibir_quantidade_palpites
    la a0, quantidade_tentativas
    lw a0, 0(a0)
    call exibir_inteiro
    j finalizar_programa

exibir_quantidade_palpites:
    la a0, quantidade_palpites
    li a7, 4
    ecall
    ret

# Chamada do sistema para encerrar o programa
finalizar_programa:
    li a7, 10
    ecall
