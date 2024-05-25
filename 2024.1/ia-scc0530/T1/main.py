from collections import deque
import heapq
import math
import matplotlib.pyplot as plt


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
    nodes_visited = 0  # Contador de nós visitados

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
    nodes_visited = 0  # Contador de nós visitados

    while heap:
        estimated_cost, current = heapq.heappop(heap)
        nodes_visited += 1

        if current == end:
            return estimated_cost, nodes_visited

        for neighbor, cost in graph.adj_list[current]:
            if not visited[neighbor]:
                heuristic_cost = cost_to_end(
                    graph, neighbor, end
                )  # Heurística: custo estimado até o final
                total_cost += cost
                heapq.heappush(heap, (total_cost + heuristic_cost, neighbor))
                visited[neighbor] = True

    return float("inf"), nodes_visited  # Se não houver caminho


def euclidean_distance(pos1, pos2):
    return math.sqrt((pos2[0] - pos1[0]) ** 2 + (pos2[1] - pos1[1]) ** 2)


def cost_to_end(graph, start, end):
    # Calcula a distância euclidiana entre os vértices
    start_pos = graph.positions[start]
    end_pos = graph.positions[end]
    return euclidean_distance(start_pos, end_pos)


# Exemplo de uso
vertices = ["A", "B", "C", "D", "E", "F", "Z"]
edges = [
    ("A", "B", 4),
    ("A", "C", 3),
    ("B", "F", 5),
    ("B", "E", 12),
    ("C", "E", 10),
    ("C", "D", 7),
    ("D", "E", 2),
    ("F", "Z", 16),
    ("E", "Z", 5),
]
graph = Graph(vertices)
graph.add_vertex("A", (0, 0))
graph.add_vertex("B", (2, 2))
graph.add_vertex("C", (2, -2))
graph.add_vertex("D", (4, -4))
graph.add_vertex("E", (6, -2))
graph.add_vertex("F", (6, 2))
graph.add_vertex("Z", (10, 4))
for edge in edges:
    graph.add_edge(*edge)

start_vertex = "A"
end_vertex = "Z"

# Printa exemplo
nodes = {
    "a": (0, 0),
    "b": (2, 2),
    "c": (2, -2),
    "d": (4, -4),
    "e": (6, -2),
    "f": (6, 2),
    "z": (10, 0),
}

edges = [
    ("a", "b"),
    ("a", "c"),
    ("b", "f"),
    ("b", "e"),
    ("c", "d"),
    ("c", "e"),
    ("d", "e"),
    ("e", "z"),
    ("f", "z"),
]

plt.figure(figsize=(8, 6))

for node, pos in nodes.items():
    plt.scatter(pos[0], pos[1], color="purple", zorder=5)
    plt.text(pos[0], pos[1], node, fontsize=12, ha="center", va="center", zorder=10)

for edge in edges:
    start_node = edge[0]
    end_node = edge[1]
    start_pos = nodes[start_node]
    end_pos = nodes[end_node]
    plt.plot(
        [start_pos[0], end_pos[0]], [start_pos[1], end_pos[1]], color="orange", zorder=1
    )

plt.xlabel("X")
plt.ylabel("Y")
plt.title("Representação do Grafo")
plt.grid(True)
plt.gca().set_aspect("equal", adjustable="box")
plt.savefig("graph_representation.png")

# BFS
total_cost_bfs, nodes_visited_bfs = bfs_minimize_cost(graph, start_vertex)

# A*
total_cost_astar, nodes_visited_astar = astar_minimize_cost(
    graph, start_vertex, end_vertex
)

print("BFS:")
print(f"Custo total da rede: {total_cost_bfs}")
print(f"Nós visitados: {nodes_visited_bfs}")

print("\nA*:")
print(f"Custo total da rede: {total_cost_astar}")
print(f"Nós visitados: {nodes_visited_astar}")
