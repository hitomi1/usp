#include "Graph.h"

#include <stdio.h>
#include <stdlib.h>

int CriarGrafo(GrafoMatriz* g, int n) {
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

int InserirAresta(GrafoMatriz* g, int u, int v) {
    // Endereco do grafo e vertices da aresta a ser criada
    if (g->nVertices <= 0 || u >= g->nVertices || v >= g->nVertices) {
        // Se algum parametro for invalido
        return 0;  // Erro
    }

    // Define a aresta sem direcao entre u,v
    g->vertices[u][v] = 1;
    g->vertices[v][u] = 1;
    return 1;  // Sucesso
}

int RemoverAresta(GrafoMatriz* g, int u, int v) {
    // Endereo do grafo e vertices da aresta a ser removida
    // Se algum parametro for invalido
    if (g->nVertices <= 0 || u >= g->nVertices || v >= g->nVertices) {
        return 0;  // Erro
    }
    // Apaga a aresta(mesmo se ela nao existir)
    g->vertices[u][v] = 0;
    g->vertices[v][u] = 0;
    return 1;  // Sucesso
}

void ExibirGrafo(GrafoMatriz* g) {
    // Endereco do grafo a ser exibido
    int totalArcs = 0;
    for (int i = 0; i < g->nVertices; i++) {
        for (int j = 0; j < g->nVertices; j++) {
            if (g->vertices[i][j] == 1) {
                totalArcs++;
            }
        }
    }
    printf("Total of vertices: %d, total of arcs: %d\n", g->nVertices,
           totalArcs / 2);

    for (int i = 0; i < g->nVertices; i++) {
        // Cada volta representa a i-esima linha da Matriz
        int printed = 0;
        printf("Vertex %d, arcs:", i);
        for (int j = 0; j < g->nVertices; j++) {
            if (g->vertices[i][j] == 1) {
                if (printed > 0) {
                    printf(",");
                }
                printf(" %d", j);
                printed++;
            }
        }
        // Pula uma linha apos exibir todos os elementos da i-esima linha
        printf("\n");
    }
}

int DeletarGrafo(GrafoMatriz* g) {
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
void DFSUtil(GrafoMatriz* g, int v, int* visited) {
    visited[v] = 1;
    printf("visited %d\n", v);
    for (int i = 0; i < g->nVertices; i++) {
        if (g->vertices[v][i] && !visited[i]) {
            DFSUtil(g, i, visited);
        }
    }
}

void DFS(GrafoMatriz* g, int startVertex) {
    int* visited = (int*)malloc(g->nVertices * sizeof(int));
    for (int i = 0; i < g->nVertices; i++) {
        visited[i] = 0;
    }
    DFSUtil(g, startVertex, visited);
    free(visited);
}

void BFS(GrafoMatriz* g, int startVertex) {
    int* visited = (int*)malloc(g->nVertices * sizeof(int));
    for (int i = 0; i < g->nVertices; i++) {
        visited[i] = 0;
    }
    int queue[g->nVertices];
    int front = -1, rear = -1;
    queue[++rear] = startVertex;
    visited[startVertex] = 1;
    while (front != rear) {
        int currentVertex = queue[++front];
        printf("visited %d\n", currentVertex);
        for (int i = 0; i < g->nVertices; i++) {
            if (g->vertices[currentVertex][i] && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
    free(visited);
}