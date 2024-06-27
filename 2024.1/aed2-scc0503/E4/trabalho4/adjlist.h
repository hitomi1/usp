#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "limits.h"

#define Vertex int
typedef struct node *Link;
typedef struct graph *Digraph;
#define Graph Digraph

struct node {
    Vertex w;
    Link next;
    int weight;
    bool visited;
};

struct graph {
    int V;
    int A;
    Link *adj;
};

Graph initGraph(int n) {
    Graph G = (Graph)malloc(sizeof(*G));
    G->V = n;
    G->A = 0;
    G->adj = (Link *)malloc(n * sizeof(Link));
    for (int i; i < n; i++) {
        G->adj[i] = NULL;
    }
    return G;
}

void destroyGraph(Graph G) {
    if (G != NULL) {
        for (int i; i < G->V; i++) {
            free(G->adj[i]);
        }
        free(G->adj);
        free(G);
    }
}

Link newArc(Vertex w, int weight) {
    Link anode = (Link)malloc(sizeof(*anode));
    anode->w = w;
    anode->next = NULL;
    anode->weight = weight;
    anode->visited = false;
    return anode;
}

void insertArc(Graph G, Vertex v, Vertex w, int weight) {
    if (G->adj[v] == NULL) {
        G->adj[v] = newArc(w, weight);
        G->A++;
    } else {
        for (Link p = G->adj[v]; p != NULL; p = p->next) {
            if (p->w == w) {  // se w já existe na lista de adjacencia de v
                return;
            }
            if (p->next == NULL) {  // insere arco no final da lista
                p->next = newArc(w, weight);
                G->A++;
            }
        }
    }
}

void insertEdge(Graph G, Vertex v, Vertex w, int weight) {
    insertArc(G, v, w, weight);
    insertArc(G, w, v, weight);
}

void removeArc(Graph G, Vertex v, Vertex w) {
    if (v > G->V) {
        return;
    }
    Link prev = G->adj[v];
    for (Link p = G->adj[v]; p != NULL; p = p->next) {
        if (p->w == w) {
            G->A--;
            if (G->adj[v] == p) {
                G->adj[v] = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            return;
        } else {
            prev = p;
        }
    }
}

void removeEdge(Graph G, Vertex v, Vertex w) {
    removeArc(G, v, w);
    removeArc(G, w, v);
}

void printGraph(Graph G) {
    printf("Graph, %d vertex and %d arcs\n", G->V, G->A);
    for (int i = 0; i < G->V; i++) {
        printf("Vertex %d: ", i);
        for (Link p = G->adj[i]; p != NULL; p = p->next) {
            printf(" %d > %d / ", i, p->w);
        }
        printf("\n");
    }
}

void clearVisited(Graph G) {
    for (int i = 0; i < G->V; i++) {
        G->adj[i]->visited = false;
    }
}

void DFS(Graph G, Vertex x) {
    G->adj[x]->visited = true;
    printf("visited %d \n", x);
    for (Link p = G->adj[x]; p != NULL; p = p->next) {
        Vertex y = p->w;
        if (!(G->adj[y]->visited)) {
            DFS(G, y);
        }
    }
}

void startDFS(Graph G, Vertex x) {
    clearVisited(G);
    printf("DFS\n");
    DFS(G, x);
}

void BFS(Graph G, Vertex x) {
    Vertex *queue = (Vertex *)malloc(sizeof(Vertex) * G->V);
    int start = 0, end = 0;
    queue[end++] = x;
    while (start != end) {
        Vertex elem = queue[start++];
        if (!(G->adj[elem]->visited)) {
            G->adj[elem]->visited = true;
            printf("visited %d \n", elem);
            for (Link p = G->adj[elem]; p != NULL; p = p->next) {
                Vertex w = p->w;
                if (!(G->adj[w]->visited)) {
                    queue[end++] = w;
                }
            }
        }
    }
    free(queue);
}

void startBFS(Graph G, Vertex x) {
    clearVisited(G);
    printf("BFS\n");
    BFS(G, x);
}

void topologicalSortingBFS(Digraph D) {
    Vertex queue[D->V];
    int start = 0, end = 0;
    int in[D->V];
    for (int i = 0; i < D->V; i++) {
        in[i] = 0;
    }
    for (int i = 0; i < D->V; i++) {
        for (Link p = D->adj[i]; p != NULL; p = p->next) {
            in[p->w]++;
        }
    }
    for (int x = 0; x < D->V; x++) {
        if (in[x] == 0) {
            queue[end++] = x;
        }
    }
    printf("Topological Sorting BFS\n");
    while (start != end) {
        Vertex v = queue[start++];
        printf("%d ", v);
        for (Link p = D->adj[v]; p != NULL; p = p->next) {
            in[p->w]--;
            if (in[p->w] == 0) {
                queue[end++] = p->w;
            }
        }
    }
    if (D->V != start) {
        printf("\n Not a DAG!");
    }
}

void TSDFS(Digraph D, Vertex x, int *in) {
    if (in[x] == 0) {
        printf("%d ", x);
        in[x]--;
        for (Link p = D->adj[x]; p != NULL; p = p->next) {
            in[p->w]--;
            TSDFS(D, p->w, in);
        }
    }
}

void topologicalSortDFS(Digraph D) {
    int *in = (int *)calloc(D->V, sizeof(int));
    for (int i = 0; i < D->V; i++) {
        for (Link p = D->adj[i]; p != NULL; p = p->next) {
            in[p->w]++;
        }
    }
    printf("Topological Sorting DFS\n");
    for (Vertex x = 0; x < D->V; x++) {
        TSDFS(D, x, in);
    }
    free(in);
}

bool simplePath(Graph G, Vertex start, Vertex end) {
    G->adj[start]->visited = true;
    for (Link p = G->adj[start]; p != NULL; p = p->next) {
        if (p->w == end) {
            return true;
        }
        if (G->adj[p->w]->visited == false) {
            if (simplePath(G, p->w, end)) {
                return true;
            }
        }
    }
    return false;
}

void startSimplePath(Graph G, Vertex start, Vertex end) {
    clearVisited(G);
    if (simplePath(G, start, end)) {
        printf("Simple path %d--%d exists!\n", start, end);
    } else {
        printf("Simple path %d--%d does NOT exists!\n", start, end);
    }
}

Graph copyGraph(Graph G) {
    Graph C = initGraph(G->V);
    for (int i = 0; i < G->V; i++) {
        for (Link p = G->adj[i]; p != NULL; p = p->next) {
            insertEdge(C, i, p->w, p->weight);
        }
    }
    return C;
}

int euler(Graph C, Vertex x, int *stack, int *index) {
    while (C->adj[x] != NULL) {
        (*index)++;
        stack[*index] = x;
        Vertex w = C->adj[x]->w;
        removeEdge(C, x, w);
        x = w;
    }
    return 1;
}

void eulerPath(Graph G, Vertex v, Vertex end) {
    Graph C = copyGraph(G);
    Vertex *stack = (Vertex *)malloc(sizeof(Vertex) * G->V);
    int index = -1;
    printf("\nEuler Path:\n");
    printf("%d", end);
    while (euler(C, v, stack, &index) && index >= 0) {
        v = stack[index--];
        printf("- %d", v);
    }
    free(stack);
    // destroyGraph(C);
}

void checkEulerPath(Graph G) {
    int *degree = (int *)calloc(G->V, sizeof(int));
    Vertex *odds = (Vertex *)calloc(3, sizeof(Vertex));
    int n_odd = 0;
    for (int i = 0; i < G->V; i++) {
        for (Link p = G->adj[i]; p != NULL; p = p->next) {
            degree[i]++;
        }
        if (degree[i] % 2 != 0) {
            odds[n_odd] = i;
            n_odd++;
            if (n_odd > 2) {
                printf("An Euler path does NOT exist.");
                free(degree);
                return;
            }
        }
    }
    if (n_odd == 2) {
        printf("An Euler path exists.");
        eulerPath(G, odds[0], odds[1]);
    }
    if (n_odd == 0) {
        printf("An Euler circle exists.");
        eulerPath(G, 0, 0);
    }
    if (n_odd == 1) {
        printf("An Euler path does NOT exist.");
    }
}

bool hamiltonPath(Graph G, Vertex start, Vertex end, int n) {
    if (start == end) {
        if (((n + 1) == G->V)) {
            return true;
        } else if (n != 0) {
            return false;
        }
    }
    G->adj[start]->visited = true;
    for (Link p = G->adj[start]; p != NULL; p = p->next) {
        if (!(G->adj[p->w]->visited)) {
            if (hamiltonPath(G, p->w, end, n + 1)) {
                printf("%d >> %d\n", start, p->w);
                return true;
            }
        }
    }
    G->adj[start]->visited = false;
    return false;
}

bool startHamiltonPath(Graph G, Vertex start, Vertex end) {
    clearVisited(G);
    printf("\nHamilton Path:\n");
    return hamiltonPath(G, start, end, 0);
}

void dijkstra(Graph G, Vertex s) {
    int *distance = (int *)malloc(sizeof(int) * G->V);
    Vertex *parent = (Vertex *)malloc(sizeof(Vertex) * G->V);
    for (int i = 0; i < G->V; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        if (G->adj[i] != NULL) {
            G->adj[i]->visited = false;
        }
    }
    Vertex v = s;
    distance[s] = 0;
    while (G->adj[v] != NULL && G->adj[v]->visited == false) {
        G->adj[v]->visited = true;
        for (Link p = G->adj[v]; p != NULL; p = p->next) {
            Vertex u = p->w;
            int pdistance = INT_MAX;
            if (distance[v] != INT_MAX) {
                pdistance = distance[v] + p->weight;
            }
            if (distance[u] > pdistance) {
                distance[u] = pdistance;
                parent[u] = v;
            }
        }
        int min_dist = INT_MAX;
        v = 0;
        for (int i = 0; i < G->V; i++) {
            if ((G->adj[i] != NULL) && (G->adj[i]->visited == false) &&
                (distance[i] < min_dist)) {
                min_dist = distance[i];
                v = i;
            }
        }
    }
    printf("\nDijstra:\n");
    for (int i = 0; i < G->V; i++) {
        printf("Distance from %d to %d = %d", s, i, distance[i]);
        printf("\nReverse path: %d", i);
        Vertex path = i;
        while (path != s) {
            path = parent[path];
            printf(" <- %d", path);
        }
        printf("\n");
    }
}