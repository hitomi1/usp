#ifndef Graph
#define Graph

typedef struct {
    int nVertices;
    // Armazena o numero de vertices
    int** vertices;
    // Ponteiro para a matriz
} GrafoMatriz;

// Estrutura para representar um nó na fila de prioridade
typedef struct {
    int vertex;
    int dist;
} Node;

// Cria o grafo com espaco para n vertices
int MyGraph(GrafoMatriz* g, int n);
// Insere aresta entre os vertices u,v
int add_edge(GrafoMatriz* g, int u, int v, int w);
// Remove aresta entre os vertices u,v
int remove_edge(GrafoMatriz* g, int u, int v);
// Existe aresta entre os vertices u,v
int exist_edge(GrafoMatriz* g, int u, int v);
// Exibe na tela o grafo
void adjacency_matrix(GrafoMatriz* g);
// Exibe na tela o grafo
void print_graph(GrafoMatriz* g);
// Libera o espaco alocado pelo grafo
int delete_graph(GrafoMatriz* g);
// Retorna a lista de vertices adjacentes a determinado vertice
void get_adj_vertex(GrafoMatriz* g, int u);
// Retorna o numero de vertices
int number_of_vertex(GrafoMatriz* g);
// Retorna o numero de arestas
int number_of_edges(GrafoMatriz* g);
// Remove aresta de menor peso
int pop_lightest_edge(GrafoMatriz* g);

void allPairsShortestPaths(GrafoMatriz* g);
#endif
