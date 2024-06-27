#include <stdio.h>

#include "Graph.h"

// Le o numero de vertices e cria o grafo
void IniciarGrafo(GrafoMatriz* g) {  
    // Endereco do grafo
    int aux;
    scanf("%d", &aux);   // Le o numero de vertices o grafo deve possuir
    CriarGrafo(g, aux);  // Cria o grafo
}

int main() {
    GrafoMatriz g;  // Reserva espaco para um grafo

    int x, y;

    IniciarGrafo(&g);  // Inicia o programa

    while (scanf("%d %d\n", &x, &y) != EOF) {
        // Le quais os vertices da nova aresta
        InserirAresta(&g, x, y);  // Insere a aresta
    }
    printf("DFS\n");
    DFS(&g, 0);
    printf("BFS\n");
    BFS(&g, 0);
    // ExibirGrafo(&g);  // Exibe o grafo
    // RemoverAresta(g, x, y);  // Remove a aresta
    DeletarGrafo(&g);  // Deleta o grafo
    return 0;
}
