from collections import deque


# Função para verificar se a posição (x, y) é válida e caminhável
def is_valid(x, y, maze, visited):
    M, N = len(maze), len(maze[0])
    return 0 <= x < M and 0 <= y < N and maze[x][y] == 0 and not visited[x][y]


# Função BFS para encontrar a menor distância até a saída
def bfs(maze):
    M, N = len(maze), len(maze[0])
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # cima, baixo, esquerda, direita
    visited = [[False] * N for _ in range(M)]
    queue = deque([(0, 0, 0)])  # (x, y, distância)
    visited[0][0] = True

    while queue:
        x, y, dist = queue.popleft()

        # Se chegarmos na saída, retornamos a distância
        if x == M - 1 and y == N - 1:
            return dist

        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if is_valid(nx, ny, maze, visited):
                visited[nx][ny] = True
                queue.append((nx, ny, dist + 1))

    return 0  # Nenhum caminho possível


# Função DFS para contar o número total de caminhos possíveis
def dfs(x, y, maze, visited, M, N):
    if x == M - 1 and y == N - 1:
        return 1  # Encontrou um caminho

    visited[x][y] = True
    total_paths = 0
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]  # cima, baixo, esquerda, direita

    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if is_valid(nx, ny, maze, visited):
            total_paths += dfs(nx, ny, maze, visited, M, N)

    visited[x][y] = False  # Desmarcar para permitir outras buscas
    return total_paths


def solve_maze(M, N, obstacles):
    # Construir o labirinto | 0 = caminho, 1 = obstáculo
    maze = [[0] * N for _ in range(M)]
    for x, y in obstacles:
        maze[x][y] = 1  # Marcar os obstáculos
    # Encontrar a menor distância usando BFS
    min_distance = bfs(maze)

    # Se não houver caminho possível, retorne 0
    if min_distance == 0:
        print("0 0")
        return

    # Contar o número de caminhos possíveis usando DFS
    visited = [[False] * N for _ in range(M)]
    total_paths = dfs(0, 0, maze, visited, M, N)

    # Imprimir o resultado
    print(total_paths, min_distance)


# Leitura do input
M, N = map(int, input().split())
obstacles = []
for _ in range(M * N):
    try:
        obstacles.append(tuple(map(int, input().split())))
    except EOFError:
        break

solve_maze(M, N, obstacles)
