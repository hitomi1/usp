#ifndef Graph
#define Graph

typedef struct {
    int nVertices;
    // Armazena o numero de vertices
    int** vertices;
    // Ponteiro para a matriz
} GrafoMatriz;

// Cria o grafo com espaco para n vertices
int CriarGrafo(GrafoMatriz* g, int n);
// Insere aresta entre os vertices u,v
int InserirAresta(GrafoMatriz* g, int u, int v);
// Remove aresta entre os vertices u,v
int RemoverAresta(GrafoMatriz* g, int u, int v);
// Exibe na tela o grafo
void ExibirGrafo(GrafoMatriz* g);
// Libera o espaco alocado pelo grafo
int DeletarGrafo(GrafoMatriz* g);
void DFS(GrafoMatriz* g, int startVertex);
void BFS(GrafoMatriz* g, int startVertex);
#endif
