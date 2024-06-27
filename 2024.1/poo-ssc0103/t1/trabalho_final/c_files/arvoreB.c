#include "arvoreB.h"

//Função para criar o arquivo de índice da árvore B
bool cria_arvore(FILE *arq_dados, FILE *arq_index_arvB){
    //Criando o registro de cabeçalho
    REGISTRO_CABECA_ARVORE_B cranio;

    //preenchendo o registro de cabeçalho
    cranio.status  = '0';
    cranio.noRaiz  =  -1;
    cranio.proxRRN =   0;
    cranio.nroChaves = 0;

    //Escrevendo o registro de cabeçalho no arquivo
    fwrite(&cranio.status, sizeof(char),1, arq_index_arvB);
    fwrite(&cranio.noRaiz, sizeof(int),1, arq_index_arvB);
    fwrite(&cranio.proxRRN, sizeof(int),1, arq_index_arvB);
    fwrite(&cranio.nroChaves, sizeof(int),1, arq_index_arvB);

    


    return true;
}