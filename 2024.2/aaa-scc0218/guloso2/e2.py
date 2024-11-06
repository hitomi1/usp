def max_custo(tarefas):
    # Ordenar as tarefas pelo tempo limite (d)
    tarefas.sort(key=lambda x: x[1])

    # Inicialização das variáveis
    tempo_atual = 0
    custo_total = 0

    # Processar cada tarefa
    for t, d in tarefas:
        tempo_atual += t
        custo_total += d - tempo_atual

    return custo_total


# Leitura da entrada
n = int(input())

tarefas = [tuple(map(int, input().split())) for _ in range(n)]
print(tarefas)
# Calcular e imprimir o custo máximo
print(max_custo(tarefas))
