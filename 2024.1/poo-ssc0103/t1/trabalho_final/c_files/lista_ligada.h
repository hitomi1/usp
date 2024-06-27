#ifndef LISTA_H
#define LISTA_H

#define SUCESSO 1
#define NAO_EXISTE -1
#define JA_EXISTE -2
#define INVALIDO -3
#define CHEIA -4
#define VAZIA -5
#include <stdio.h>

typedef int t_chave;

typedef struct {
	// t_chave chave;
	char removido;
    int tamanhoRegistro;
    long int prox;
    long int byteOfset;
    int id;
    int idade;
    int tamNomeJog;
    char nomeJogador[100];
    int tamNacionalidade;
    char nacionalidade[100];
    int tamNomeClube;
    char nomeClube[100];
} t_elemento;


typedef struct t_no *t_apontador;

typedef struct t_no {
	t_elemento elemento;
	t_apontador proximo;
    t_apontador anterior;
} t_no;


typedef struct {
	t_apontador primeiro;
	// outras coisas como contador, ultimo, etc
} t_lista;

void remover_sem_ID(FILE *arq, FILE *arq_binario_index, char _arq_index[], t_lista *l);
void escreve_lista(t_lista *lista, FILE *arq);
void inicializar(t_lista *l);
void libera_lista(t_lista *l);
void inserir(t_elemento e, t_lista *l);
void inserir_ordenado(t_elemento e, t_lista *l);
// int remover(t_chave chave, t_lista *l);
void _remover(char *campo, char *valorS, char valorI, t_lista *l);
// t_elemento pesquisar(t_chave chave, t_lista *l);
int vazia(t_lista *l);
// int cheia(t_lista *l);
void imprimir(t_lista *l);
#endif