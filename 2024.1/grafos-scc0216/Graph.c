#include "Graph.h"

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
    g->vertices[v][u] = w;
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
