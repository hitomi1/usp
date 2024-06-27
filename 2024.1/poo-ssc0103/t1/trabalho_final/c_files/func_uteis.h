#include <ctype.h>
#include <stdbool.h>
#include "lista_ligada.h"
#include "ler_escrever_arqs.h"

typedef struct{
	char *nomeCampo;
	char *valorCampo;
	int id_idade;
}NOME_VALOR;

typedef struct{
	int m;
	NOME_VALOR* campos;
}QUANT_BUSCAS;

bool inserir_na_lista_de_removidos(FILE *arq, FILE *arq_binario_index, long int byteOffset_index, REGISTRO_DADOS d);
bool remover_por_ID(FILE *arq, FILE *arq_binario_index,char nome_arquivo_index[], char valor_campo[], int id_numerico);
bool remover_registro(int qtd_campos, FILE *arq, FILE *arq_binario_index, QUANT_BUSCAS* b);
void binarioNaTela(char *nomeArquivoBinario);
t_lista busca_registro(FILE *arq, QUANT_BUSCAS* b, int n_busca, int flag_imprime, FILE *arq_binario_index, char _arq_index[]);
void scan_quote_string(char *str);
void imprime_registros(int TAM_NJ, int TAM_N, int TAM_CJ, char nj[], char n[], char cj[]);
void _erros(int er);
bool removendo_registro_fisicamente(FILE *arq,FILE  *arq_binario_index,char nome_arquivo_index[], long int byteOffset_index, REGISTRO_DADOS d);