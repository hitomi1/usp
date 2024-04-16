# Implementação de Grafo em C

Este projeto oferece uma implementação simples de uma estrutura de dados de
grafo em C, seguindo o formato TAD (Tipo de Dado Abstrato). A implementação
inclui funções para criar um grafo com N vértices, verificar se uma aresta
existe, adicionar e remover arestas, imprimir informações do grafo e mais.

## Alunos:

- Adhemar Molon Neto - 14687681
- Felipe da Costa Coqueiro - 11781361
- Fernando Alee Suaiden - 12680836
- Gustavo Hitomi da Silva - 11801202
- Luiz Fellipe Catuzzi Araujo Hotoshi - 11871198

## Arquivos

- `graph.c`: Contém a implementação das funções do grafo.
- `graph.h`: Contém as declarações das funções do grafo.
- `main.c`: Contém a função principal para testar a implementação do grafo.

## Uso

Para compilar o projeto, execute:

`make` ou `make all`

Isso irá gerar um executável chamado `main`. Você pode então executar o
executável para testar a implementação do grafo manualmente:

`make run` ou `./main `

Para testar com o input fornecido:

`make run < 1.in` ou `./main < 1.in`

## Funções Principais

- `MyGraph(GrafoMatriz* g, int n)`: Cria um grafo com N vértices.
- `add_edge(GrafoMatriz* g, int u, int v, int w)`: Adiciona uma aresta entre os vértices u e v com peso w.
- `remove_edge(GrafoMatriz* g, int u, int v)`: Remove a aresta entre os vértices u e v.
- `exist_edge(GrafoMatriz* g, int u, int v)`: Verifica se existe uma aresta entre os vértices u e v.
- `adjacency_matrix(GrafoMatriz* g)`: Imprime a matriz de adjacência do grafo.
- `print_graph(GrafoMatriz* g)`: Imprime informações sobre o grafo, incluindo o total de vértices, o total de arestas e as arestas de cada vértice.
- `get_adj_vertex(GrafoMatriz* g, int u)`: Imprime as arestas do vértice u.
- `number_of_vertex(GrafoMatriz* g)`: Retorna o número de vértices do grafo.
- `number_of_edges(GrafoMatriz* g)`: Retorna o número de arestas do grafo.
- `pop_lightest_edge(GrafoMatriz* g)`: Remove a aresta de menor peso do grafo.
- `delete_graph(GrafoMatriz* g)`: Remove o grafo.
