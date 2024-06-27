#include "Graph.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int MyGraph(GrafoMatriz* g, int n) {
    // Endereco do grafo a ser criado e numero de vertices do grafo
    g->nVertices = n;
    // Salva no grafo o numero de vertices
    if (n <= 0) {
        // Se numero de vertices for invalido
        return 0;  // Erro
    }
    g->vertices = (int**)malloc(n * sizeof(int*));
    // Reserva espaco para vetor de int*
    for (int i = 0; i < n; i++) {
        // Reserva vetores de int
        g->vertices[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            g->vertices[i][j] = 0;
        }
    }
    return 1;  // Sucesso
}

int add_edge(GrafoMatriz* g, int u, int v, int w) {
    // Endereco do grafo e vertices da aresta a ser criada
    if (g->nVertices <= 0 || u >= g->nVertices || v >= g->nVertices) {
        // Se algum parametro for invalido
        return 0;  // Erro
    }
    printf("Adicionando aresta entre %d e %d com peso %d\n", u, v, w);
    // Define a aresta entre u,v com peso w
    g->vertices[u][v] = w;
    // g->vertices[v][u] = w;
    return 1;  // Sucesso
}

int remove_edge(GrafoMatriz* g, int u, int v) {
    // Endereo do grafo e vertices da aresta a ser removida
    // Se algum parametro for invalido
    if (g->nVertices <= 0 || u >= g->nVertices || v >= g->nVertices ||
        g->vertices[u][v] == 0) {
        return 0;  // Erro
    }
    printf("Removendo aresta entre %d e %d com peso %d\n", u, v,
           g->vertices[u][v]);

    // Apaga a aresta entre u e v
    g->vertices[u][v] = 0;
    g->vertices[v][u] = 0;
    return 1;  // Sucesso
}

int exist_edge(GrafoMatriz* g, int u, int v) {
    // Endereo do grafo e vertices da aresta a ser verificada
    // Se algum parametro for invalido
    if (g->nVertices <= 0 || u >= g->nVertices || v >= g->nVertices) {
        return 0;  // Erro
    }
    printf("Verificando existencia de aresta entre %d e %d\n", u, v);
    // Retorna True se a aresta existir
    return g->vertices[u][v] >= 1;
}

void adjacency_matrix(GrafoMatriz* g) {
    // Endereco do grafo a ser exibido
    for (int i = 0; i < g->nVertices; i++) {
        // Cada volta representa a i-esima linha da Matriz
        for (int j = 0; j < g->nVertices; j++) {
            printf("%d ", g->vertices[i][j]);
        }
        printf("\n");
    }
}

void print_graph(GrafoMatriz* g) {
    // Endereco do grafo a ser exibido

    printf("Total de vértices: %d, total de arestas: %d\n", g->nVertices,
           number_of_edges(g));

    for (int i = 0; i < g->nVertices; i++) {
        // Cada volta representa a i-esima linha da Matriz
        int printed = 0;
        printf("Vertice %d, arestas: {", i);
        for (int j = 0; j < g->nVertices; j++) {
            if (g->vertices[i][j] >= 1) {
                if (printed > 0) {
                    printf(", ");
                }
                printf("(%d, %d)", i, j);
                printed++;
            }
        }
        printf("}");
        printf("\n");
    }
}

void get_adj_vertex(GrafoMatriz* g, int u) {
    // Endereco do grafo e vertice a ser verificado
    printf("Vertice %d, arestas: {", u);
    for (int j = 0; j < g->nVertices; j++) {
        if (g->vertices[u][j] >= 1) {
            printf("(%d, %d)", u, j);
        }
    }
    printf("}");
    printf("\n");
}

int number_of_vertex(GrafoMatriz* g) { return g->nVertices; }

int number_of_edges(GrafoMatriz* g) {
    int totalEdges = 0;
    for (int i = 0; i < g->nVertices; i++) {
        for (int j = 0; j < g->nVertices; j++) {
            if (g->vertices[i][j] >= 1) {
                totalEdges++;
            }
        }
    }
    return totalEdges / 2;
}

int pop_lightest_edge(GrafoMatriz* g) {
    // Endereo do grafo
    // Se algum parametro for invalido
    if (g->nVertices <= 0) {
        return 0;  // Erro
    }
    int lightestWeight = 0;
    int u, v;

    // Encontra aresta mais leve
    for (int i = 0; i < g->nVertices; i++) {
        for (int j = i + 1; j < g->nVertices; j++) {
            if (g->vertices[i][j] != 0 &&
                (lightestWeight == 0 || g->vertices[i][j] < lightestWeight)) {
                lightestWeight = g->vertices[i][j];
                u = i;
                v = j;
            }
        }
    }

    // Remove a aresta mais leve
    if (lightestWeight != 0) {
        g->vertices[u][v] = 0;
        g->vertices[v][u] = 0;
        printf("Aresta removida entre %d e %d com peso %d\n", u, v,
               lightestWeight);
    } else {
        printf("Sem arestas para remover\n");
    }

    return 1;  // Sucesso
};

int delete_graph(GrafoMatriz* g) {
    // Endereco do grafo a ser removido
    if (g->nVertices <= 0) {
        // Se o grafo for invalido
        return 0;  // Erro
    }
    for (int i = 0; i < g->nVertices; i++) {
        // Libera o cada linha da matriz
        free(g->vertices[i]);
    }
    free(g->vertices);
    // Remove o vetor com endereco de cada linha da matriz
    g->nVertices = 0;
    // Define o numero de vertices como 0
    return 1;  // Sucesso
}

// Função para criar um novo nó
Node* criarNode(int vertex, int dist) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->dist = dist;
    return newNode;
}

// Estrutura para representar a fila de prioridade
typedef struct {
    int capacity;
    int size;
    Node** array;
} PriorityQueue;

// Função para criar uma nova fila de prioridade
PriorityQueue* criarFilaPrioridade(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->capacity = capacity;
    queue->size = 0;
    queue->array = (Node**)malloc(capacity * sizeof(Node*));
    return queue;
}

// Função para trocar dois nós
void trocarNodes(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

// Função para manter a propriedade de min-heap
void minHeapify(PriorityQueue* queue, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < queue->size &&
        queue->array[left]->dist < queue->array[smallest]->dist)
        smallest = left;

    if (right < queue->size &&
        queue->array[right]->dist < queue->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        trocarNodes(&queue->array[smallest], &queue->array[idx]);
        minHeapify(queue, smallest);
    }
}

// Função para verificar se a fila de prioridade está vazia
int filaVazia(PriorityQueue* queue) { return queue->size == 0; }

// Função para extrair o nó com a menor distância da fila de prioridade
Node* extrairMin(PriorityQueue* queue) {
    if (filaVazia(queue)) return NULL;

    Node* root = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    queue->size--;
    minHeapify(queue, 0);

    return root;
}

// Função para diminuir a distância de um vértice na fila de prioridade
void diminuirChave(PriorityQueue* queue, int vertex, int dist) {
    int i;
    for (i = 0; i < queue->size; i++) {
        if (queue->array[i]->vertex == vertex) break;
    }

    if (dist < queue->array[i]->dist) {
        queue->array[i]->dist = dist;

        while (i && queue->array[i]->dist < queue->array[(i - 1) / 2]->dist) {
            trocarNodes(&queue->array[i], &queue->array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
}

// Função para encontrar os caminhos mínimos para todos os pares
void allPairsShortestPaths(GrafoMatriz* g) {
    int n = g->nVertices;
    int** dist = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dist[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            dist[i][j] = INT_MAX;
    }

    for (int src = 0; src < n; src++) {
        PriorityQueue* queue = criarFilaPrioridade(n);

        for (int i = 0; i < n; i++) {
            queue->array[i] = criarNode(i, dist[src][i]);
            queue->size++;
        }

        queue->array[src] = criarNode(src, 0);
        diminuirChave(queue, src, 0);

        while (!filaVazia(queue)) {
            Node* node = extrairMin(queue);
            int u = node->vertex;

            for (int v = 0; v < n; v++) {
                if (g->vertices[u][v] && dist[src][u] != INT_MAX &&
                    dist[src][u] + g->vertices[u][v] < dist[src][v]) {
                    dist[src][v] = dist[src][u] + g->vertices[u][v];
                    diminuirChave(queue, v, dist[src][v]);
                }
            }
            free(node); // Liberar o nó após o uso
        }

        free(queue->array); // Liberar o array de nós
        free(queue); // Liberar a fila de prioridade
    }

    // Imprimir os resultados
    printf("Matriz de distancias minimas:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++)
        free(dist[i]);
    free(dist);
}
