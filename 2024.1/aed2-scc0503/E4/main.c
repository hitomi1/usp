#include <stdio.h>

#include "Graph.h"
// Le o numero de vertices e cria o grafo
void InitGraph(GrafoMatriz* g) {
    // Endereco do grafo
    int aux;
    scanf("%d", &aux);
    // Le o numero de vertices o grafo deve possuir
    MyGraph(g, aux);
    // Cria o grafo
}
/*
void GerenciarOperacoes(GrafoMatriz* g) {
    // Endereco do grafo
    int op = 10, u, v, w;
    // Le a quantidade de operacoes a serem feitas
    while (op != 0) {
        printf(
            "\n+-------------------------Escolha sua "
            "operação-------------------------+\n");
        printf("| 1 - Adicionar aresta             | ");
        printf("2 - Remover aresta                |\n");
        printf("| 3 - Verificar se aresta existe   | ");
        printf("4 - Exibir matriz de adjacencia   |\n");
        printf("| 5 - Exibir grafo                 | ");
        printf("6 - Verificar vertices adjacentes |\n");
        printf("| 7 - Verificar numero de vertices | ");
        printf("8 - Verificar numero de arestas   |\n");
        printf("| 9 - Remover aresta de menor peso | ");
        printf("0 - Encerrar                      |\n");
        printf(
            "+--------------------------------------"
            "--------------------------------+\n");
        // Le qual operacao deve ser feita
        scanf("%d", &op);
        printf("\n");
        switch (op) {
            case 1:
                printf("Insira uma aresta: \n");
                // Le quais os vertices da nova aresta
                scanf("%d %d %d", &u, &v, &w);
                // Insere a aresta
                if (add_edge(g, u, v, w)) {
                    printf("Aresta adicionada\n");
                } else {
                    printf("Aresta nao adicionada\n");
                }
                break;
            case 2:
                printf("Remova uma aresta: \n");
                // Le quais os vertices da aresta a ser removida
                scanf("%d %d", &u, &v);

                // Remove a aresta
                if (remove_edge(g, u, v)) {
                    printf("Aresta removida\n");
                } else {
                    printf("Aresta nao existe\n");
                };
                break;
            case 3:
                printf("Verifique se uma aresta existe: \n");
                // Le qual aresta deve ser verificada
                scanf("%d %d", &u, &v);
                // Remove a aresta
                if (exist_edge(g, u, v)) {
                    printf("Aresta existe\n");
                } else {
                    printf("Aresta nao existe\n");
                };
                break;
            case 4:
                // Exibe a matriz de adjacencia
                printf("Matriz de adjacencia:\n");
                adjacency_matrix(g);
                break;
            case 5:
                // Exibe o grafo
                print_graph(g);
                break;
            case 6:
                // Le qual vertice deve ser verificado
                printf("Insira um vertice: \n");
                scanf("%d", &u);
                // Retorna os vertices adjacentes
                get_adj_vertex(g, u);
                break;
            case 7:
                // Retorna o numero de vertices
                printf("O grafo possui %d vertices\n", number_of_vertex(g));
                break;
            case 8:
                // Retorna o numero de vertices
                printf("O grafo possui %d arestas\n", number_of_edges(g));
                break;
            case 9:
                // Remove aresta de menor peso
                pop_lightest_edge(g);
                break;
        }
    }
    printf("Operacoes encerradas\n");
}
*/
int main() {
    // Reserva espaco para um grafo
    GrafoMatriz g;

    printf("Insira o numero de vertices do grafo\n");
    // Inicia o programa
    InitGraph(&g);

    add_edge(&g, 0, 1, 2);
    add_edge(&g, 0, 2, 7);
    add_edge(&g, 1, 2, 3);
    add_edge(&g, 2, 1, 2);
    add_edge(&g, 1, 3, 8);
    add_edge(&g, 1, 4, 5);
    add_edge(&g, 2, 3, 1);
    add_edge(&g, 3, 4, 5);
    add_edge(&g, 4, 3, 4);

    adjacency_matrix(&g);
    // print_graph(&g);
    allPairsShortestPaths(&g); 
    // Deleta o grafo
    delete_graph(&g);
    return 0;
}
