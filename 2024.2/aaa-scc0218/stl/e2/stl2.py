import heapq


# Número de consultas
n = int(input())


# Lista de consultas (heap de min para garantir a ordem de processamento)

consultas = []

# Lendo as consultas e adicionando ao heap
for _ in range(n):
    entrada = input().split()

    id_consulta = int(entrada[1])
    intervalo = int(entrada[2])
    heapq.heappush(consultas, (intervalo, id_consulta, intervalo))


# Número de resultados K
k = int(input())

# Lista para armazenar os K primeiros resultados
resultados = []

# Processando as consultas
for _ in range(k):
    tempo, id_consulta, intervalo = heapq.heappop(consultas)
    resultados.append(id_consulta)
    # Agendando a próxima execução dessa consulta
    heapq.heappush(consultas, (tempo + intervalo, id_consulta, intervalo))

# Imprimindo os resultados
for resultado in resultados:
    print(resultado)
