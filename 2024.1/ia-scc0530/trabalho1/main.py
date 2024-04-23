from collections import deque
import heapq
import math

class Graph:
    def __init__(self, vertices):
        self.vertices = vertices
        self.adj_list = {v: [] for v in vertices}
        self.positions = {}  # Armazena as coordenadas dos vértices

    def add_vertex(self, vertex, pos):
        self.positions[vertex] = pos

    def add_edge(self, u, v, cost):
        self.adj_list[u].append((v, cost))
        self.adj_list[v].append((u, cost))

def bfs_minimize_cost(graph, start):
    visited = {v: False for v in graph.vertices}
    queue = deque([(start, 0)])  # (vertex, total_cost)
    visited[start] = True
    total_cost = 0
    nodes_visited = 1  # Contador de nós visitados

    while queue:
        current, current_cost = queue.popleft()
        nodes_visited += 1

        for neighbor, cost in graph.adj_list[current]:
            if not visited[neighbor]:
                queue.append((neighbor, current_cost + cost))
                visited[neighbor] = True
                total_cost += current_cost + cost

    return total_cost, nodes_visited

def astar_minimize_cost(graph, start, end):
    heap = [(0, start)]  # (estimated_cost, vertex)
    visited = {v: False for v in graph.vertices}
    visited[start] = True
    total_cost = 0
    nodes_visited = 1  # Contador de nós visitados

    while heap:
        estimated_cost, current = heapq.heappop(heap)
        nodes_visited += 1

        if current == end:
            return int(estimated_cost), nodes_visited

        for neighbor, cost in graph.adj_list[current]:
            if not visited[neighbor]:
                heuristic_cost = cost_to_end(graph, neighbor, end)  # Heurística: custo estimado até o final
                total_cost += cost
                heapq.heappush(heap, (total_cost + heuristic_cost, neighbor))
                visited[neighbor] = True

    return float('inf'), nodes_visited  # Se não houver caminho

def euclidean_distance(pos1, pos2):
    return math.sqrt((pos2[0] - pos1[0])**2 + (pos2[1] - pos1[1])**2)

def cost_to_end(graph, start, end):
    # Calcula a distância euclidiana entre os vértices
    start_pos = graph.positions[start]
    end_pos = graph.positions[end]
    return euclidean_distance(start_pos, end_pos)

# Exemplo de uso
vertices = ['A', 'B', 'C', 'D', 'E', 'F', 'Z']
edges = [('A', 'B', 9), ('A', 'C', 4), ('A', 'D', 7), ('B', 'E', 1),
         ('C', 'F', 12), ('D', 'F', 14), ('E', 'Z', 5), ('F', 'Z', 9)]
graph = Graph(vertices)
graph.add_vertex('A', (1, 4))
graph.add_vertex('B', (2, 6))
graph.add_vertex('C', (3, 5))
graph.add_vertex('D', (1, 2))
graph.add_vertex('E', (3, 2))
graph.add_vertex('F', (4, 3))
graph.add_vertex('Z', (5, 4))
for edge in edges:
    graph.add_edge(*edge)

start_vertex = 'A'
end_vertex = 'Z'

# BFS
total_cost_bfs, nodes_visited_bfs = bfs_minimize_cost(graph, start_vertex)

# A*
total_cost_astar, nodes_visited_astar = astar_minimize_cost(graph, start_vertex, end_vertex)

print("BFS:")
print(f"Custo total da rede: {total_cost_bfs}")
print(f"Nós visitados: {nodes_visited_bfs}")

print("\nA*:")
print(f"Custo total da rede: {total_cost_astar}")
print(f"Nós visitados: {nodes_visited_astar}")
