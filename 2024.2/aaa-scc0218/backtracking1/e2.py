# Função DFS para encontrar o caminho mais longo
def dfs(u, length, graph, visited):
    # Inicializa o caminho máximo local
    max_length_local = length

    # Explora todos os vizinhos de u
    for v in graph[u]:
        if not visited[u][v]:
            # Marca a aresta (u, v) como visitada
            visited[u][v] = visited[v][u] = True
            # Continua a busca a partir de v e armazena o maior caminho encontrado
            max_length_local = max(max_length_local, dfs(v, length + 1, graph, visited))
            # Desmarca a aresta (u, v) ao voltar (backtrack)
            visited[u][v] = visited[v][u] = False

    return max_length_local


def longest_path(n, edges):
    # Inicializa o grafo como uma lista de adjacências
    graph = [[] for _ in range(n)]

    # Adiciona as arestas ao grafo
    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)

    # Inicializa a matriz de visitados para marcar arestas
    visited = [[False] * n for _ in range(n)]
    overall_max_length = 0

    # Inicia a DFS a partir de cada nó
    for u in range(n):
        overall_max_length = max(overall_max_length, dfs(u, 0, graph, visited))

    return overall_max_length


# Leitura dos casos de teste
while True:
    # Leitura de n (número de farmácias) e m (número de arestas)
    n, m = map(int, input().split())

    # Condição de parada
    if n == 0 and m == 0:
        break

    # Leitura das arestas
    edges = [tuple(map(int, input().split())) for _ in range(m)]

    # Calcula o caminho mais longo para o caso atual
    result = longest_path(n, edges)

    # Imprime o resultado
    print(result)
