
#include <stdlib.h>
#include <string.h>
#include "lista_ligada.h"
#include "func_uteis.h"

void inicializar(t_lista *l) {
	// idealmente, limpar a lista que TALVEZ exista
	l->primeiro = NULL;
}

void libera_lista(t_lista *l){ // conferir
	if(l != NULL){
		t_apontador p;
		while(l->primeiro != NULL){
			p = l->primeiro;
			l->primeiro = p->proximo;
			free(p);
		}
	}
}

// insercao no inicio
void inserir(t_elemento e, t_lista *l) { 
	if(l == NULL){
		printf("lista nao existe\n");
		return;
	}

	t_apontador p = (t_apontador) malloc(sizeof(t_no));
	if (p == NULL) {
		printf("Memoria cheia!\n");
		return;
	}
	p->elemento = e;
	p->proximo = NULL;
	
	if(l->primeiro == NULL){
		p->anterior = NULL;
		l->primeiro = p;
		return;
	}

	t_apontador p1 = l->primeiro;
	t_apontador p2;
	while(p1 != NULL){
		p2 = p1;
		p1 = p1->proximo;
	}
	
	p2->proximo = p;
	p->anterior = p2;
}

void inserir_ordenado(t_elemento e, t_lista *l){
	if(l == NULL){
		printf("lista nao existe\n");
		return;
	}
	
	t_apontador p = (t_apontador) malloc(sizeof(t_no));
	if (p == NULL) {
		printf("Memoria cheia!\n");
		return;
	}
	p->elemento = e;
	p->proximo = NULL;

	if(l->primeiro == NULL){
		p->anterior = NULL;
		l->primeiro = p;
		return;
	}

	t_apontador p1 = l->primeiro;
	t_apontador p2;
	//insere no começo
	if(e.id < p1->elemento.id && (p1->elemento.id == l->primeiro->elemento.id)){
		l->primeiro = p;
		p1->anterior = p;
		p->proximo = p1;
		return;
	}
	//insere no meio
	while(p1 != NULL){
		if(e.id < p1->elemento.id ){
			p2->proximo = p;
			p1->anterior = p;
			p->proximo = p1;
			p->anterior = p2;
			return;
		}
		p2 = p1;
		p1 = p1->proximo;
	}
	//insere no fim
	p2->proximo = p;
	p->anterior = p1;
}

void _remover(char *campo, char *valorS, char valorI, t_lista *l) {
	if (vazia(l)) { // conferir
		printf("Lista vazia\n");
		exit(1);
	}

	t_apontador p;
	t_apontador p2; // aux
	t_apontador p3;

	if(strcmp(campo, "idade") == 0){
		p = l->primeiro;
		while (p != NULL) {
			if (p->elemento.idade != valorI) {
					p2 = p->proximo;
				if(p->anterior != NULL){
					p->anterior->proximo = p->proximo;
				}
				if(p->proximo != NULL){
					p->proximo->anterior = p->anterior;
				}
				if(l->primeiro == p){
					l->primeiro = p2;
				}
				free(p);
				p = p2;
			}
			else{
				p = p->proximo;
			}
		}
	}

	if(strcmp(campo, "nomeJogador") == 0){
		p = l->primeiro;
		while (p != NULL) {
			if ((strncmp(p->elemento.nomeJogador, valorS, p->elemento.tamNomeJog) != 0) || p->elemento.tamNomeJog == 0) {
					p2 = p->proximo;
				if(p->anterior != NULL){
					p->anterior->proximo = p->proximo;
				}
				if(p->proximo != NULL){
					p->proximo->anterior = p->anterior;
				}
				if(l->primeiro == p){
					l->primeiro = p2;
				}
				free(p);
				p = p2;
			}
			else{
				p = p->proximo;
			}
		}
	}

	if(strcmp(campo, "nacionalidade") == 0){
		p = l->primeiro;
		while (p != NULL) {
			if ((strncmp(p->elemento.nacionalidade, valorS, p->elemento.tamNacionalidade) != 0) || p->elemento.tamNacionalidade == 0) {
					p2 = p->proximo;
				if(p->anterior != NULL){
					p->anterior->proximo = p->proximo;
				}
				if(p->proximo != NULL){
					p->proximo->anterior = p->anterior;
				}
				if(l->primeiro == p){
					l->primeiro = p2;
				}
				free(p);
				p = p2;
			}
			else{
				p = p->proximo;
			}
		}
	}

	if(strcmp(campo, "nomeClube") == 0){
		p = l->primeiro;
		while (p != NULL) {
			if ((strncmp(p->elemento.nomeClube, valorS, p->elemento.tamNomeClube) != 0) || p->elemento.tamNomeClube == 0) {
					p2 = p->proximo;
				if(p->anterior != NULL){
					p->anterior->proximo = p->proximo;
				}
				if(p->proximo != NULL){
					p->proximo->anterior = p->anterior;
				}
				if(l->primeiro == p){
					l->primeiro = p2;
				}
				free(p);
				p = p2;
			}
			else{
				p = p->proximo;
			}
		}
	}
}

int vazia(t_lista *l) {

	if (l->primeiro == NULL)
		return 1;

	return 0;

}

void imprimir(t_lista *l) {

	t_apontador p = l->primeiro;

	if(p == NULL){
		_erros(2);
		return;
	}

	while (p != NULL) {

		if(p->elemento.tamNomeJog == 0) printf("Nome do Jogador: SEM DADO\n");
		else printf("Nome do Jogador: %.*s\n", (p->elemento.tamNomeJog), p->elemento.nomeJogador);
					        
		if(p->elemento.tamNacionalidade == 0) printf("Nacionalidade do Jogador: SEM DADO\n");
		else printf("Nacionalidade do Jogador: %.*s\n", (p->elemento.tamNacionalidade), p->elemento.nacionalidade);
					        
		if(p->elemento.tamNomeClube == 0) printf("Clube do Jogador: SEM DADO\n");
		else printf("Clube do Jogador: %.*s\n", (p->elemento.tamNomeClube), p->elemento.nomeClube);
        
		printf("id: %d\n", p->elemento.id);
		printf("\n");

		p = p->proximo;
	}
}

void escreve_lista(t_lista *l, FILE *arq){
	t_apontador p = l->primeiro;
	if(p == NULL){
		_erros(2);
		return;
	}
	while (p != NULL) {
		fwrite(&p->elemento.id, sizeof(int), 1, arq);
		fwrite(&p->elemento.byteOfset, sizeof(long int), 1, arq);
		p = p->proximo;
	}
}

void remover_sem_ID(FILE *arq, FILE *arq_binario_index, char _arq_index[], t_lista *l){
	t_apontador p = l->primeiro;

	if(p == NULL){
		//_erros(2);
		return;
	}

	while (p != NULL) {
		remover_por_ID(arq, arq_binario_index, _arq_index, "0", p->elemento.id);
		p = p->proximo;
	}
}
