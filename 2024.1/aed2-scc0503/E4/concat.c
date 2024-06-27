#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nVertices;
    // Armazena o numero de vertices
    int** vertices;
    // Ponteiro para a matriz
} GrafoMatriz;

typedef struct {
    int vertice;
    int custo;
} ParVerticeCusto;

typedef struct {
    ParVerticeCusto* array;
    int tamanho;
} FilaPrioridade;

FilaPrioridade* criarFilaPrioridade(int tamanho) {
    FilaPrioridade* fila = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    fila->array = (ParVerticeCusto*)malloc(tamanho * sizeof(ParVerticeCusto));
    fila->tamanho = 0;
    return fila;
}

void destruirFilaPrioridade(FilaPrioridade* fila) {
    free(fila->array);
    free(fila);
}

void inserir(FilaPrioridade* fila, int vertice, int custo) {
    int i = fila->tamanho;
    fila->tamanho++;
    while (i > 0 && fila->array[(i - 1) / 2].custo > custo) {
        fila->array[i] = fila->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    fila->array[i].vertice = vertice;
    fila->array[i].custo = custo;
}

ParVerticeCusto extrairMinimo(FilaPrioridade* fila) {
    ParVerticeCusto minimo = fila->array[0];
    fila->tamanho--;
    fila->array[0] = fila->array[fila->tamanho];
    int i = 0;
    while ((2 * i) + 1 < fila->tamanho) {
        int filho = (2 * i) + 1;
        if (filho + 1 < fila->tamanho &&
            fila->array[filho + 1].custo < fila->array[filho].custo) {
            filho++;
        }
        if (fila->array[filho].custo < fila->array[i].custo) {
            ParVerticeCusto temp = fila->array[i];
            fila->array[i] = fila->array[filho];
            fila->array[filho] = temp;
            i = filho;
        } else {
            break;
        }
    }
    return minimo;
}

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
    // printf("Adicionando aresta entre %d e %d com peso %d\n", u, v, w);
    // Define a aresta entre u,v com peso w
    g->vertices[u][v] = w;
    // g->vertices[v][u] = w;
    return 1;  // Sucesso
}

void imprimirCaminho(int* predecessores, int v) {
    if (predecessores[v] == -1) {
        printf("%d", v);
        return;
    }
    imprimirCaminho(predecessores, predecessores[v]);
    printf(" -> %d", v);
}

void allPairsShortestPaths(GrafoMatriz* g) {
    for (int i = 0; i < g->nVertices; i++) {
        int* distancias = (int*)malloc(g->nVertices * sizeof(int));
        int* predecessores = (int*)malloc(g->nVertices * sizeof(int));
        for (int j = 0; j < g->nVertices; j++) {
            distancias[j] = INT_MAX;
            predecessores[j] = -1;  // Inicializa todos os predecessores como -1
        }
        distancias[i] = 0;
        for (int k = 0; k < g->nVertices - 1; k++) {
            for (int u = 0; u < g->nVertices; u++) {
                for (int v = 0; v < g->nVertices; v++) {
                    if (g->vertices[u][v] && distancias[u] != INT_MAX &&
                        distancias[u] + g->vertices[u][v] < distancias[v]) {
                        distancias[v] = distancias[u] + g->vertices[u][v];
                        predecessores[v] = u;  // Atualiza o predecessor de v
                    }
                }
            }
        }
        printf("Node %d:\n", i);
        for (int j = 0; j < g->nVertices; j++) {
            printf("Distance from %d to %d = ", i, j);
            if (distancias[j] == INT_MAX) {
                printf("infinity\n");
            } else {
                printf("%d\n", distancias[j]);
                if (distancias[j] != 0) {
                    printf("Path: ");
                    imprimirCaminho(predecessores, j);
                    printf("\n");
                }
            }
        }
        if (i + 1 < g->nVertices) {
            printf("\n");
        }

        free(distancias);
        free(predecessores);
    }
}

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

void InitGraph(GrafoMatriz* g) {
    // Endereco do grafo
    int aux;
    scanf("%d", &aux);
    // Le o numero de vertices o grafo deve possuir
    MyGraph(g, aux);
    // Cria o grafo
}

int main() {
    // Reserva espaco para um grafo
    GrafoMatriz g;

    // printf("Insira o numero de vertices do grafo\n");
    // Inicia o programa
    int n, x, y, weight;
    InitGraph(&g);

    while (scanf("%d %d %d\n", &x, &y, &weight) != EOF) {
        // insertEdge(G, x, y, weight);
        add_edge(&g, x, y, weight);
    }

    allPairsShortestPaths(&g);
    // Deleta o grafo
    delete_graph(&g);
    return 0;
}
