#include "func_uteis.h"
#include "lista_ligada.h"


void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

//Função para imprimir os campos variáveis do registro
void imprime_registros(int TAM_NJ, int TAM_N, int TAM_CJ, char nj[], char n[], char cj[]){
	if(TAM_NJ == 0) printf("Nome do Jogador: SEM DADO\n");
	else printf("Nome do Jogador: %.*s\n", TAM_NJ, nj);
		
	if(TAM_N == 0) printf("Nacionalidade do Jogador: SEM DADO\n");
	else printf("Nacionalidade do Jogador: %.*s\n", TAM_N, n);
		
	if(TAM_CJ == 0) printf("Clube do Jogador: SEM DADO\n");
	else printf("Clube do Jogador: %.*s\n", TAM_CJ, cj);
		
	printf("\n");
}

//Função que realiza a funcionalidade 3
t_lista busca_registro(FILE *arq, QUANT_BUSCAS* b, int n_busca, int flag_imprime, FILE *arq_binario_index, char _arq_index[]){
	t_elemento e;
	t_lista l;

	int registro_existe = 0;

	//Lista para armazenar os elementos que serão imprimidos
	inicializar(&l);

	
	fseek(arq, 0, SEEK_SET);
	//Registro de cabeçalho e de dados
	REGISTRO_CABECA c;
	REGISTRO_DADOS d;

	// Lendo as inforacoes do cabecalho
	fread(&c.status, sizeof(char), 1, arq);
	fread(&c.topo, sizeof(long int), 1, arq);
	fread(&c.proxByteOffset, sizeof(long int), 1, arq);
	fread(&c.nroRegArq, sizeof(int), 1, arq);
	fread(&c.nroRegRem, sizeof(int), 1, arq);

	int byte_regs = 25;
	
	//Laço que contabiliza a quantidade de buscas
	for(int j = 0; j < n_busca; j++){	
		if(flag_imprime == 1)	
			printf("Busca %d\n\n", (j+1));
	    //Se a quantidade de buscas foi igual a 1
		if(b[j].m == 1){
			int conta_reg = 0;

			//Lê os registros procurando pelo solicitado
		    while(conta_reg < c.nroRegArq){
				//fprintf(stderr, "regs: %d\n", conta_reg);
				REGISTRO_DADOS d;
				fread(&d.removido, sizeof(char), 1, arq);
				fread(&d.tamanhoRegistro, sizeof(int), 1, arq);
				fread(&d.prox, sizeof(long int), 1, arq);
				fread(&d.id, sizeof(int), 1, arq);
				fread(&d.idade, sizeof(int), 1, arq);
				fread(&d.tamNomeJog, sizeof(int), 1, arq);
				fread(&d.nomeJogador, sizeof(char), (d.tamNomeJog), arq);
				d.nomeJogador[d.tamNomeJog] = '\0';
				fread(&d.tamNacionalidade, sizeof(int), 1, arq);
				d.nacionalidade[d.tamNacionalidade] = '\0';
				fread(&d.nacionalidade, sizeof(char), (d.tamNacionalidade), arq);
				fread(&d.tamNomeClube, sizeof(int), 1, arq);
				d.nomeClube[d.tamNomeClube] = '\0';
				fread(&d.nomeClube, sizeof(char), (d.tamNomeClube), arq);
				byte_regs += d.tamanhoRegistro;
				if(d.removido == '1'){
					continue;
				}

				e.removido = d.removido;
				e.tamanhoRegistro = d.tamanhoRegistro;
				e.prox = d.prox;
				e.id = d.id;
				e.idade = d.idade;
				e.tamNomeJog = d.tamNomeJog;
				strncpy(e.nomeJogador, d.nomeJogador, d.tamNomeJog);
				e.nomeJogador[d.tamNomeJog] = '\0';
				e.tamNacionalidade = d.tamNacionalidade;
				strncpy(e.nacionalidade, d.nacionalidade, d.tamNacionalidade);
				e.nacionalidade[d.tamNacionalidade] = '\0';
				e.tamNomeClube = d.tamNomeClube;
				strncpy(e.nomeClube, d.nomeClube, d.tamNomeClube);
				e.nomeClube[d.tamNomeClube] = '\0';
				
				//Se encontrar um campo que seja igual, imprime
			    if(strcmp(b[j].campos[0].nomeCampo, "id") == 0){
			    	if(b[j].campos[0].id_idade == d.id && flag_imprime == 1){
					    imprime_registros(d.tamNomeJog, d.tamNacionalidade, d.tamNomeClube, d.nomeJogador, d.nacionalidade, d.nomeClube);
			        }
		    	}
		    	if(strcmp(b[j].campos[0].nomeCampo, "idade") == 0){
		    		if(b[j].campos[0].id_idade == d.idade && flag_imprime == 1){
					    imprime_registros(d.tamNomeJog, d.tamNacionalidade, d.tamNomeClube, d.nomeJogador, d.nacionalidade, d.nomeClube);
		    	    }
					else if(b[j].campos[0].id_idade == d.idade){
						remover_por_ID(arq, arq_binario_index, _arq_index, "0", d.id);
						fseek(arq, byte_regs, SEEK_SET);
					}
		    	}
		    	if(strcmp(b[j].campos[0].nomeCampo, "nomeJogador") == 0 ){
		    		if(strncmp(b[j].campos[0].valorCampo, d.nomeJogador, d.tamNomeJog) == 0){
					    if(d.tamNomeJog != 0 && flag_imprime == 1){
					    	imprime_registros(d.tamNomeJog, d.tamNacionalidade, d.tamNomeClube, d.nomeJogador, d.nacionalidade, d.nomeClube);
					    }
						else if(d.tamNomeJog != 0){ 
							remover_por_ID(arq, arq_binario_index, _arq_index,"0", d.id);
							fseek(arq, byte_regs, SEEK_SET);
						}
		    	    }
		    	}
		    	if(strcmp(b[j].campos[0].nomeCampo, "nacionalidade") == 0 ){
					if(strncmp(b[j].campos[0].valorCampo, d.nacionalidade, d.tamNacionalidade) == 0){
					    if(d.tamNacionalidade != 0 && flag_imprime == 1){
					    	imprime_registros(d.tamNomeJog, d.tamNacionalidade, d.tamNomeClube, d.nomeJogador, d.nacionalidade, d.nomeClube);
					    }
						else if(d.tamNacionalidade != 0) {
							remover_por_ID(arq, arq_binario_index, _arq_index,"0", d.id);
							fseek(arq, byte_regs, SEEK_SET);
						}
					}
		    	}
		    	if(strcmp(b[j].campos[0].nomeCampo, "nomeClube") == 0){
		    		if(strncmp(b[j].campos[0].valorCampo, d.nomeClube, d.tamNomeClube) == 0){
					    if(d.tamNomeClube != 0 && flag_imprime == 1){
					    	imprime_registros(d.tamNomeJog, d.tamNacionalidade, d.tamNomeClube, d.nomeJogador, d.nacionalidade, d.nomeClube);
					    }
						else if(d.tamNomeClube != 0){
							remover_por_ID(arq, arq_binario_index, _arq_index,"0", d.id);
							fseek(arq, byte_regs, SEEK_SET);
						}
		    	    }	
		    	}
		    	conta_reg++;
		   	}
		}

		//Se a quantidade de buscas for diferente de 1
		else{
			//Laço para realizar as buscas
			for(int i = 0; i < b[j].m; i++){
				//Se i igual a 0, quer dizer que estamos no primeiro item da busca, então lê o arquivo e realiza a inserção na lista
				if(i == 0){
					int conta_reg = 0;
					//Laço para ler o arquivo
					while(conta_reg < c.nroRegArq){
						fread(&d.removido, sizeof(char), 1, arq);
						fread(&d.tamanhoRegistro, sizeof(int), 1, arq);
						fread(&d.prox, sizeof(long int), 1, arq);
						fread(&d.id, sizeof(int), 1, arq);
						fread(&d.idade, sizeof(int), 1, arq);
						fread(&d.tamNomeJog, sizeof(int), 1, arq);
						fread(&d.nomeJogador, sizeof(char), (d.tamNomeJog), arq);
						d.nomeJogador[d.tamNomeJog] = '\0';
						fread(&d.tamNacionalidade, sizeof(int), 1, arq);
						fread(&d.nacionalidade, sizeof(char), (d.tamNacionalidade), arq);
						d.nacionalidade[d.tamNacionalidade] = '\0';
						fread(&d.tamNomeClube, sizeof(int), 1, arq);
						fread(&d.nomeClube, sizeof(char), (d.tamNomeClube), arq);
						d.nomeClube[d.tamNomeClube] = '\0';

						//Se encontrar um id igual, imprime
					    if(strcmp(b[j].campos[i].nomeCampo, "id") == 0){
							if(b[j].campos[i].id_idade == d.id){
								imprime_registros(d.tamNomeJog, d.tamNacionalidade, d.tamNomeClube, d.nomeJogador, d.nacionalidade, d.nomeClube);
						   	}
					   	}
					   	//Se encontrar registros com campos igual, insere na lista
						if(strcmp(b[j].campos[i].nomeCampo, "idade") == 0 && d.removido != '1'){
							if(b[j].campos[i].id_idade == d.idade){
						    	e.removido = d.removido;
						        e.tamanhoRegistro = d.tamanhoRegistro;
						        e.prox = d.prox;
						        e.id = d.id;
						        e.idade = d.idade;
						        e.tamNomeJog = d.tamNomeJog;
						        strncpy(e.nomeJogador, d.nomeJogador, d.tamNomeJog);
						        e.nomeJogador[d.tamNomeJog] = '\0';
						        e.tamNacionalidade = d.tamNacionalidade;
						        strncpy(e.nacionalidade, d.nacionalidade, d.tamNacionalidade);
						        e.nacionalidade[d.tamNacionalidade] = '\0';
						        e.tamNomeClube = d.tamNomeClube;
						        strncpy(e.nomeClube, d.nomeClube, d.tamNomeClube);
						        e.nomeClube[d.tamNomeClube] = '\0';
						        inserir(e, &l);
						    }
						}
						if(strcmp(b[j].campos[i].nomeCampo, "nomeJogador") == 0 && d.removido != '1'){
						    if(strcmp(b[j].campos[i].valorCampo, d.nomeJogador) == 0){
						    	e.removido = d.removido;
						        e.tamanhoRegistro = d.tamanhoRegistro;
						        e.prox = d.prox;
						        e.id = d.id;
						        e.idade = d.idade;
						        e.tamNomeJog = d.tamNomeJog;
						        strcpy(e.nomeJogador, d.nomeJogador);
						        e.tamNacionalidade = d.tamNacionalidade;
						        strcpy(e.nacionalidade, d.nacionalidade);
						        e.tamNomeClube = d.tamNomeClube;
						        strcpy(e.nomeClube, d.nomeClube);
						        inserir(e, &l);
						    }
						}
						if(strcmp(b[j].campos[i].nomeCampo, "nacionalidade") == 0 && d.removido != '1'){
						   	if(strcmp(b[j].campos[i].valorCampo, d.nacionalidade) == 0){
						   		e.removido = d.removido;
						   	    e.tamanhoRegistro = d.tamanhoRegistro;
						   	    e.prox = d.prox;
						   	    e.id = d.id;
						   	    e.idade = d.idade;
						   	    e.tamNomeJog = d.tamNomeJog;
						   	    strcpy(e.nomeJogador, d.nomeJogador);
						   	    e.tamNacionalidade = d.tamNacionalidade;
						   	    strcpy(e.nacionalidade, d.nacionalidade);
						   	    e.tamNomeClube = d.tamNomeClube;
						   	    strcpy(e.nomeClube, d.nomeClube);
						   	    inserir(e, &l);
						   	}
						}
						if(strcmp(b[j].campos[i].nomeCampo, "nomeClube") == 0 && d.removido != '1'){
						   	if(strcmp(b[j].campos[i].valorCampo, d.nomeClube) == 0){
						   		e.removido = d.removido;
						   	    e.tamanhoRegistro = d.tamanhoRegistro;
						   	    e.prox = d.prox;
						   	    e.id = d.id;
						   	    e.idade = d.idade;
						   	    e.tamNomeJog = d.tamNomeJog;
						   	    strcpy(e.nomeJogador, d.nomeJogador);
						   	    e.tamNacionalidade = d.tamNacionalidade;
						   	    strcpy(e.nacionalidade, d.nacionalidade);
						   	    e.tamNomeClube = d.tamNomeClube;
						   	    strcpy(e.nomeClube, d.nomeClube);
						   	    inserir(e, &l);
						   	}	
						}
						conta_reg++;
					}
				}
				// caso nao tenha o primeiro item da busca, vou remover os itens que sao diferentes do que estou buscando da minha lista
				else{
					_remover(b[j].campos[i].nomeCampo, b[j].campos[i].valorCampo, b[j].campos[i].id_idade, &l);
				}
				// se estou no ultimo loop do laço da realização das buscas, imprimo a minha lista
				if(i == (b[j].m-1) && flag_imprime == 1){
					imprimir(&l);
				}
				else if(i == (b[j].m-1)){
					remover_sem_ID(arq, arq_binario_index, _arq_index, &l);
				}
			}
		}
		//Volta ao início do arquivo
		fseek(arq, 25, SEEK_SET); 
	}
	return l;
}

//Função para impressão de erros
void _erros(int er){
	switch(er){
		case 1:
		    printf("Falha no processamento do arquivo.\n");
		    exit(0);
			break;
		case 2:
			printf("Registro inexistente.\n\n");
			break;
	}
}

bool remover_por_ID(FILE *arq, FILE *arq_binario_index, char nome_arquivo_index[],char valor_campo[], int id_numerico){
	int id;
	long int byteOffset_index;
	int byte_index = 1;
	int id_procurado;
	if(id_numerico == 0){
		id_procurado = captura_id_e_idade(valor_campo);
	}
	else id_procurado = id_numerico;
	 
	fseek(arq_binario_index, sizeof(char), SEEK_SET);
	while(fread(&id, sizeof(int), 1, arq_binario_index)){
		if(id == id_procurado){
			fread(&byteOffset_index, sizeof(long int), 1, arq_binario_index);

			REGISTRO_DADOS d;
			fseek(arq, byteOffset_index, SEEK_SET);
			fread(&d.removido, sizeof(char), 1, arq);
			if(d.removido == '1'){
				return false;
			}
			fread(&d.tamanhoRegistro, sizeof(int), 1, arq);
			fread(&d.prox, sizeof(long int), 1, arq);
			fread(&d.id, sizeof(int), 1, arq);
			fread(&d.idade, sizeof(int), 1, arq);
			fread(&d.tamNomeJog, sizeof(int), 1, arq);
			fread(&d.nomeJogador, sizeof(char), (d.tamNomeJog), arq);
			fread(&d.tamNacionalidade, sizeof(int), 1, arq);
			fread(&d.nacionalidade, sizeof(char), (d.tamNacionalidade), arq);
			fread(&d.tamNomeClube, sizeof(int), 1, arq);
			fread(&d.nomeClube, sizeof(char), (d.tamNomeClube), arq);

			return removendo_registro_fisicamente(arq, arq_binario_index, nome_arquivo_index, byteOffset_index, d);
		}
		fread(&byteOffset_index, sizeof(long int), 1, arq_binario_index);
		byte_index += 12;
	}
	return false;
}

bool inserir_na_lista_de_removidos(FILE *arq, FILE *arq_binario_index, long int byteOffset_index, REGISTRO_DADOS d){
	long int topo;
	int fim = -1;
	char removido = '1';
	fseek(arq, 1, SEEK_SET);
	fread(&topo, sizeof(long int), 1, arq);
	//lista vazia
	if(topo == -1){
		//Removendo o registro do arquivo de dados
		fseek(arq, byteOffset_index, SEEK_SET);
		fwrite(&removido, sizeof(char), 1, arq);
		fwrite(&d.tamanhoRegistro, sizeof(int), 1, arq);	
		fwrite(&fim, sizeof(int), 1, arq);
		//modificando o topo
		fseek(arq, 1, SEEK_SET);
		fwrite(&byteOffset_index, sizeof(long int), 1, arq);
	}
	else{
		fseek(arq, topo + 1, SEEK_SET);
		int tam_reg_removido;
		fread(&tam_reg_removido, sizeof(int), 1, arq);
		//topo é maior que novo elemento (insere no início)
		if(tam_reg_removido > d.tamanhoRegistro){
			//modificando o topo
			fseek(arq, 1, SEEK_SET);
			fwrite(&byteOffset_index, sizeof(long int), 1, arq);
			//Removendo o registro do arquivo de dados
			fseek(arq, byteOffset_index, SEEK_SET);
			fwrite(&removido, sizeof(char), 1, arq);
			fwrite(&d.tamanhoRegistro, sizeof(int), 1, arq);	
			fwrite(&topo, sizeof(long int), 1, arq);
			return true;
		}
		//insere no meio dos registros dos removidos
		long int bof = topo; //(bof -> byteofset)
		long int bof_anterior = topo;
		fseek(arq, bof+1, SEEK_SET);
		while(fread(&tam_reg_removido, sizeof(int), 1, arq)){
			if(tam_reg_removido > d.tamanhoRegistro){
				fseek(arq, bof_anterior + 5, SEEK_SET);
				fwrite(&byteOffset_index, sizeof(long int), 1, arq);

				fseek(arq, byteOffset_index, SEEK_SET);
				fwrite(&removido, sizeof(char), 1, arq);
				fwrite(&d.tamanhoRegistro, sizeof(int), 1, arq);	
				fwrite(&bof, sizeof(long int), 1, arq);
				return true;
			}
			bof_anterior = bof;
			fread(&bof, sizeof(long int), 1, arq);
			if(bof == -1)break;
			fseek(arq, bof+1, SEEK_SET);
		}
		//insere no fim dos registros dos removidos
		fseek(arq, bof_anterior + 5, SEEK_SET);
		fwrite(&byteOffset_index, sizeof(long int), 1, arq);
		//remove registro
		fseek(arq, byteOffset_index, SEEK_SET);
		fwrite(&removido, sizeof(char), 1, arq);
		fwrite(&d.tamanhoRegistro, sizeof(int), 1, arq);	
		fwrite(&fim, sizeof(int), 1, arq);	
	}
	return true;
}

bool removendo_registro_fisicamente(FILE *arq, FILE* arq_binario_index, char nome_arquivo_index[], long int byteOffset_index, REGISTRO_DADOS d){
	fseek(arq, 17, SEEK_SET);
	int numero_regs;
	fread(&numero_regs, sizeof(int), 1, arq);
	fseek(arq, 17, SEEK_SET);
	numero_regs--;
	fwrite(&numero_regs, sizeof(int), 1, arq);
	fseek(arq, 21, SEEK_SET);
	int numero_removidos;
	fread(&numero_removidos, sizeof(int), 1, arq);
	fseek(arq, 21, SEEK_SET);
	numero_removidos++;
	fwrite(&numero_removidos, sizeof(int), 1, arq);

	if(inserir_na_lista_de_removidos(arq, arq_binario_index, byteOffset_index, d)){
		FILE *novo_arquivo_index = fopen(nome_arquivo_index, "wb");
		fseek(arq, 0 , SEEK_SET);
		ler_escrever_aquivo_index(arq, novo_arquivo_index);
		fclose(novo_arquivo_index);
		fseek(arq, 0 , SEEK_SET);
		return true;
	}
	return false;
}