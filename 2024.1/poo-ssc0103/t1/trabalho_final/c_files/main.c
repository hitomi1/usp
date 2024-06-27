#include "func_uteis.h"


QUANT_BUSCAS* buscas(int n){
	QUANT_BUSCAS* b = malloc(n * sizeof(QUANT_BUSCAS));
	b[0].m = 0;

	//Armazena a quantidade de buscas e os campos a serem buscados
	for(int i = 0; i <= (n-1); i++){
		scanf("%d", &b[i].m);
		int cont = 0;
		while(cont < b[i].m){

			if(cont == 0){
				b[i].campos = malloc(b[i].m * sizeof(NOME_VALOR));
			}
			char *str1 = malloc(50 * sizeof(char));
			char *str2 = malloc(50 * sizeof(char));

			scanf("%s", str1);
			scan_quote_string(str2);

			if(strcmp(str1, "id") == 0){
				b[i].campos[cont].id_idade = atoi(str2);
			}
			else if(strcmp(str1, "idade") == 0){
				b[i].campos[cont].id_idade = atoi(str2);
			}

			b[i].campos[cont].nomeCampo = str1;
			b[i].campos[cont].valorCampo = str2;

			cont++;
		}
	}
	return b;
}

int main(){
	//Recebe a funcionalidade a ser executada
	int funcionalidade;
	scanf("%d ", &funcionalidade);
	
	//Ponteiro para um arquivo
	FILE *arq;

	//Analisa qual das 3 possibilidades recebeu
	switch(funcionalidade){
		//Ler e escrever arquivo binário
		case 1:
			//lê os nomes do arquivos
			char *arq_csv = malloc(50 * sizeof(char));
			char *arq_bin = malloc(50 * sizeof(char));

			scanf("%200[^ ]", arq_csv);

			scanf("%200[^\n]", arq_bin);

			// remover o espaco que tem na frente da segunda palavra
			if(isspace(arq_bin[0])){
				for(int i = 0; i < sizeof(arq_bin); i++){
					arq_bin[i] = arq_bin[i+1];
					if(i == (sizeof(arq_bin)-1)){
						arq_bin[i] = '\0';
					}
				}
			}

			//Abrindo o arquivo "Jogador.csv"
			arq = fopen(arq_csv, "r");
			if(arq == NULL){
				_erros(1);
			}

			//Criando e abrindo o arquivo binario
			FILE *novo_arq;
			novo_arq = fopen(arq_bin, "wb");
			if(novo_arq == NULL){
				_erros(1);
			}

			//Chama a função "ler_escrever_aquivo" para realizar a funçionalidade 1
			ler_escrever_aquivo(arq, novo_arq);

			//Fecha os arquivos
			fclose(arq);
		    fclose(novo_arq);
			//Chama a função binário na tela para comparação com o run codes
			binarioNaTela(arq_bin);
			//Libera a memória dos nomes dos arquivos
		    free(arq_csv);
		    free(arq_bin);
			break;
		//Imprime os registros do arquivo binário
		case 2:
			//Lê o nome do arquivo binário e abre para leitura
			char *_arq_bin = malloc(50 * sizeof(char));

			scanf("%200[^\n]", _arq_bin);

			arq = fopen(_arq_bin, "rb");
			//ERRO
			if(arq == NULL){
			    _erros(1);
			}

			//Chama a função "recuperacao_dados" para a impressão de registros
			recuperacao_dados(arq);

			/*Libera a memória usada para armazenar o nome do arquivo
			e fecha o arquivo binário*/
			free(_arq_bin);
			fclose(arq);
			break;

		//Busca registros e imprime os encontrados
		case 3:
			//Aloca memória para nome do arquivo a ser lido
			char *_arq = malloc(50 * sizeof(char));
			t_lista l;
			int n;

			scanf("%200[^ ]", _arq);
			scanf("%d", &n);

			QUANT_BUSCAS* b = buscas(n);

			//Abre o arquivo
			arq = fopen(_arq, "rb");
			if(arq == NULL){
				_erros(1);
			}
			
			//Chama a função "busca_registro" para realizar a funçionalidade 3(últimos dois paramentros apenas para ocupar os parametros)
			busca_registro(arq, b, n,1 , arq, "nome");

			//libera memória e fechar arquivos
			free(_arq);
			for(int i = 0; i < n; i++){
				free(b[i].campos);
			}
			free(b);
			fclose(arq);
			break;

		// default:
		// 	printf("Opcao invalida.\n"); //conferir isso aqui
		// 	break;
		case 4:
			char *arq_bin_dados = malloc(50 * sizeof(char));
			char *arq_bin_indices = malloc(50 * sizeof(char));

			scanf("%200[^ ]", arq_bin_dados);

			scanf("%200[^\n]", arq_bin_indices);

			if(isspace(arq_bin_indices[0])){
				for(int i = 0; i < sizeof(arq_bin_indices); i++){
					arq_bin_indices[i] = arq_bin_indices[i+1];
					if(i == (sizeof(arq_bin_indices)-1)){
						arq_bin_indices[i] = '\0';
					}
				}
			} 
			
			FILE *ARQ_BIN_DADOS = fopen(arq_bin_dados, "rb");
			if(ARQ_BIN_DADOS == NULL){
				_erros(1);
			}
			strcat(arq_bin_indices, ".bin");
			FILE *novo_arq_index = fopen(arq_bin_indices, "wb");
			if(novo_arq_index == NULL){
				_erros(1);
			}

			ler_escrever_aquivo_index(ARQ_BIN_DADOS, novo_arq_index);
			fclose(ARQ_BIN_DADOS);
			fclose(novo_arq_index);

			binarioNaTela(arq_bin_indices);
			free(arq_bin_indices);
			free(arq_bin_dados);
			break;
		case 5:
			//Lê o nome do arquivo binário e abre para leitura
			char *_arq_bin_ = malloc(50 * sizeof(char));

			//Pega o nome do arquivo binário
			scanf("%s", _arq_bin_);

			arq = fopen(_arq_bin_, "rb + wb");
			//ERRO
			if(arq == NULL){
			    _erros(1);
			}
			//----------------------------------------------------
			char *_arq_index = malloc(50 * sizeof(char));

			//Pega o nome do arquiv de indices
			scanf("%s", _arq_index);

			FILE *arq_binario_index = fopen(_arq_index, "rb + wb");
			//ERRO
			if(arq_binario_index == NULL){
			    _erros(1);
			}
			//----------------------------------------------------
			int qtd_buscas;
			t_lista lista_buscas;

			//Pega a quantidade de buscas
			scanf("%d", &qtd_buscas);

			QUANT_BUSCAS* b2 = buscas(qtd_buscas);
			int flag_break = 0;
			
			for(int i = 0; i < qtd_buscas; i++){
				for(int j = 0; j < b2[i].m; j++){
					if(strcmp(b2[i].campos[j].nomeCampo, "id") == 0){
						//precisa do arquivo de indices
						remover_por_ID(arq, arq_binario_index, _arq_index, b2[i].campos[j].valorCampo, 0);
						flag_break = 1;
						break;
					}
				}
				if(flag_break == 1) break;
			}
			//não tem id----------------
			lista_buscas = busca_registro(arq, b2, qtd_buscas, 0, arq_binario_index, _arq_index);
			
			
			fclose(arq);
			fclose(arq_binario_index);

			binarioNaTela(_arq_bin_);
			binarioNaTela(_arq_index);
			

			/*Libera a memória usada para armazenar o nome do arquivo
			e fecha o arquivo binário*/
			free(_arq_bin_);
			free(_arq_index);
			// fclose(arq);
			// fclose(arq_binario_index);
			break;
	}
    return 0;
}