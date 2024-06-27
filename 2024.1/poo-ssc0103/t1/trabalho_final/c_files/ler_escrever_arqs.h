#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "func_uteis.h"

#define BYTE_INICIO 45

/*Registro de cabeçalho*/
typedef struct registro_cabeca{
    char status; // 1 byte
    long int topo; // 8 bytes
    long int proxByteOffset; // 8 bytes
    int nroRegArq; // 4 bytes
    int nroRegRem; // 4 bytes
} REGISTRO_CABECA;

/*Registro de dados*/
typedef struct registro_dados{
    char removido; // 1 byte
    int tamanhoRegistro; // 4 bytes
    long int prox; // 8 bytes
    int id; // 4 bytes
    int idade; // 4 bytes
    int tamNomeJog; // 4 bytes
    char nomeJogador[100]; // tamanho variável
    int tamNacionalidade; // 4 bytes
    char nacionalidade[100]; // tamanho variável 
    int tamNomeClube; // 4 bytes
    char nomeClube[100]; // tamanho variável
} REGISTRO_DADOS;

//Funções usadas para escrever o arquivo binário
int conta_registros(FILE *arq);
REGISTRO_DADOS captura_dados(FILE *arq);
int captura_id_e_idade(char *string_de_numeros);
int converte_string_em_numero(char string);
int verifica_se_eh_numero(char string);
int retorna_tamanho_reg(REGISTRO_DADOS registro);
void ler_escrever_aquivo();
//Função usada para a funcionalidade 2
void recuperacao_dados();
void ler_escrever_aquivo_index(FILE *arq_dados, FILE *novo_arq_index);
// void imprime_registro(REGISTRO_DADOS dados);