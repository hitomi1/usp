#include <stdbool.h>
#include <stdio.h>


typedef struct registro_cabeca_arvB{
    char status; // 1 byte
    int noRaiz; // 4 bytes
    int proxRRN; // 4 bytes
    int nroChaves; // 4 bytes
} REGISTRO_CABECA_ARVORE_B;

typedef struct registro_dados_arvB{
    int alturaNo;  // 4 bytes
    int nroChaves; // 4 bytes
    int C1;        // 4 bytes
    long int PR1;  // 8 bytes
    int C2;        // 4 bytes
    long int PR2;  // 8 bytes
    int C3;        // 4 bytes
    long int PR3;  // 8 bytes
    int P1;        // 4 bytes
    int P2;        // 4 bytes
    int P3;        // 4 bytes
    int P4;        // 4 bytes
} REGISTRO_DADOS_ARVORE_B;

bool cria_arvore(FILE *nome_arq_dados, FILE *nome_arq_index_arvB);