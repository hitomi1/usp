#include "func_uteis.h"

void ler_escrever_aquivo_index(FILE *arq_dados, FILE *novo_arq_index){
    int id;
    char status = '0';
    long int byte0fset;
    t_elemento e;
    t_lista lista_ordenada;

    inicializar(&lista_ordenada);

    fwrite(&status, sizeof(char), 1, novo_arq_index);

    REGISTRO_DADOS d;
    REGISTRO_CABECA c;

    fread(&c.status, sizeof(char), 1, arq_dados);
    if(c.status == '0'){
       _erros(1); 
    }
	fread(&c.topo, sizeof(long int), 1, arq_dados);
	fread(&c.proxByteOffset, sizeof(long int), 1, arq_dados);
	fread(&c.nroRegArq, sizeof(int), 1, arq_dados);
	fread(&c.nroRegRem, sizeof(int), 1, arq_dados);

    byte0fset = 25;

    fread(&d.removido, sizeof(char), 1, arq_dados);
    fread(&d.tamanhoRegistro, sizeof(int), 1, arq_dados);
    fread(&d.prox, sizeof(long int), 1, arq_dados);
    fread(&d.id, sizeof(int), 1, arq_dados);
    fread(&d.idade, sizeof(int), 1, arq_dados);
    fread(&d.tamNomeJog, sizeof(int), 1, arq_dados);
    fread(&d.nomeJogador, sizeof(char), (d.tamNomeJog), arq_dados);
    fread(&d.tamNacionalidade, sizeof(int), 1, arq_dados);
    fread(&d.nacionalidade, sizeof(char), (d.tamNacionalidade), arq_dados);
    fread(&d.tamNomeClube, sizeof(int), 1, arq_dados);
    fread(&d.nomeClube, sizeof(char), (d.tamNomeClube), arq_dados);
    
    if(d.removido != '1'){
        e.removido = d.removido;
        e.tamanhoRegistro = d.tamanhoRegistro;
        e.prox = d.prox;
        e.byteOfset = byte0fset;
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
        inserir_ordenado(e, &lista_ordenada);
    }


    byte0fset += d.tamanhoRegistro;
    int i = 0;

    while(i < ((c.nroRegArq-1) + c.nroRegRem)){

        fread(&d.removido, sizeof(char), 1, arq_dados);
        fread(&d.tamanhoRegistro, sizeof(int), 1, arq_dados);
        fread(&d.prox, sizeof(long int), 1, arq_dados);
        fread(&d.id, sizeof(int), 1, arq_dados);
        fread(&d.idade, sizeof(int), 1, arq_dados);
        fread(&d.tamNomeJog, sizeof(int), 1, arq_dados);
        fread(&d.nomeJogador, sizeof(char), (d.tamNomeJog), arq_dados);
        fread(&d.tamNacionalidade, sizeof(int), 1, arq_dados);
        fread(&d.nacionalidade, sizeof(char), (d.tamNacionalidade), arq_dados);
        fread(&d.tamNomeClube, sizeof(int), 1, arq_dados);
        fread(&d.nomeClube, sizeof(char), (d.tamNomeClube), arq_dados);

        if(d.removido != '1'){
            e.removido = d.removido;
            e.tamanhoRegistro = d.tamanhoRegistro;
            e.prox = d.prox;
            e.byteOfset = byte0fset;
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
            inserir_ordenado(e, &lista_ordenada);
        }

        byte0fset += d.tamanhoRegistro;
        //printf("%d\n", d.id);
        i++;
    }
    //printf("byte0fset: %ld\n", byte0fset);

    escreve_lista(&lista_ordenada, novo_arq_index);

    fseek(novo_arq_index, 0, SEEK_SET);
    status = '1';
    fwrite(&status, sizeof(char), 1, novo_arq_index);

    libera_lista(&lista_ordenada);
}

void ler_escrever_aquivo(FILE *arq, FILE *novo_arq){
    //Alocando memória para o registro de cabeçalho
    REGISTRO_CABECA c;

    //Inicializando registro de cabeçalho
    c.status = '0';
    c.topo = -1;
    c.proxByteOffset = 0;
    c.nroRegArq = 0;
    c.nroRegRem = 0;

    //OLHAR ISSO DEPOIS - ISSO PRECISA SER NESSA ORDEM?
    //Contando a quantidade de registros de dados
    fseek(arq, BYTE_INICIO, SEEK_SET);
    c.nroRegArq = conta_registros(arq); 

    //Voltando para o início do arquivo
    fseek(arq, BYTE_INICIO, SEEK_SET);

    c.proxByteOffset = 25;

    //Escrevendo cada campo do registro de cabeçalho
    fwrite(&c.status, sizeof(char), 1, novo_arq);
    fwrite(&c.topo, sizeof(long int), 1, novo_arq);
    fwrite(&c.proxByteOffset, sizeof(long int), 1, novo_arq);
    fwrite(&c.nroRegArq, sizeof(int), 1, novo_arq);
    fwrite(&c.nroRegRem, sizeof(int), 1, novo_arq);

    //Escrevendo os registros de dados
    int conta_reg = 0;
    REGISTRO_DADOS d;

    //Escrevendo o arquivo binário
    while(conta_reg < c.nroRegArq){
        d = captura_dados(arq);

        d.tamanhoRegistro = retorna_tamanho_reg(d);

        fwrite(&d.removido, sizeof(char), 1, novo_arq);
        fwrite(&d.tamanhoRegistro, sizeof(int), 1, novo_arq);
        fwrite(&d.prox, sizeof(long int), 1, novo_arq);
        fwrite(&d.id, sizeof(int), 1, novo_arq);
        fwrite(&d.idade, sizeof(int), 1, novo_arq);
        fwrite(&d.tamNomeJog, sizeof(int), 1, novo_arq);
        
        
        if(d.tamNomeJog != 0){
            fwrite(d.nomeJogador, sizeof(char), (d.tamNomeJog), novo_arq);
        }

        fwrite(&d.tamNacionalidade, sizeof(int), 1, novo_arq);
        if(d.tamNacionalidade != 0){
            fwrite(d.nacionalidade, sizeof(char), (d.tamNacionalidade), novo_arq);
        }

        fwrite(&d.tamNomeClube, sizeof(int), 1, novo_arq);
        if(d.tamNomeClube != 0){
            fwrite(d.nomeClube, sizeof(char), (d.tamNomeClube), novo_arq);
        }

        //Atualiza o próximo byte offset
        c.proxByteOffset += d.tamanhoRegistro;
        conta_reg++;
    }

    //Mudando o status do registro de cabeçalho
    fseek(novo_arq, 0, SEEK_SET); 
    c.status = '1';
    fwrite(&c.status, sizeof(char), 1, novo_arq);
    fseek(novo_arq, 9, SEEK_SET);
    fwrite(&c.proxByteOffset, sizeof(long int), 1, novo_arq);
}

//Função para contabilizar a quantidade de registros
int conta_registros(FILE *arq){
    int  fim_arquivo = 0;
    char caracter_atual, caracter_anterior;
    int nroRegArq = 0;

    //lê o arquivo até alcançar o fim do arquivo
    while(fim_arquivo != -1){
        fim_arquivo = fscanf(arq, "%c", &caracter_atual);
        if(caracter_atual == '\n' && caracter_anterior != '\n'){
            nroRegArq++;
        }
        caracter_anterior = caracter_atual;
    }
    if(caracter_atual != '\n'){
        nroRegArq++;
    }
    return nroRegArq;
}

//Função para preencher os campos do registro de dados
REGISTRO_DADOS captura_dados(FILE *arq){
    //Declara uma variável para o registro de dados
    REGISTRO_DADOS registro;

    //inicializa o registro de dados
    registro.removido = '0';
    registro.tamanhoRegistro = 0;
    registro.prox = -1;
    registro.id = 0;
    registro.idade = 0;
    registro.tamNomeJog = 0;
    registro.tamNacionalidade = 0;
    registro.tamNomeClube = 0;

    //string para armazenar uma linha lida do arquivo
    char string[100];
    char id[20];
    char idade[3];
    char nomeJog[50];
    char nacionalidade[50];
    char nomeClube[50];

    //Lê uma linha do arquivo quebra a linha usando "," como separador
    fgets(string, 100, arq);
    int c, c1;

    for(int i = 0; string[i] != '\0'; i++){
        if(string[i] == ','){
            //printf("%s\n", id);
            id[i] = '\0';
            c = i+1;
            break;
        }
        id[i] = string[i];
    }
    c1 = 0;
    for(int i = c; string[i] != '\0'; i++){
        if(string[i] == ','){
            idade[c1] = '\0';
            c = i+1;
            break;
        }
        idade[c1] = string[i];
        c1++;
    }
    c1 = 0;
    for(int i = c; string[i] != '\0'; i++){
        if(string[i] == ','){
            nomeJog[c1] = '\0';
            c = i+1;
            break;
        }
        nomeJog[c1] = string[i];
        c1++;
    }
    c1 = 0;
    for(int i = c; string[i] != '\0'; i++){
        if(string[i] == ','){
            nacionalidade[c1] = '\0';
            c = i+1;
            break;
        }
        nacionalidade[c1] = string[i];
        c1++;
    }
    c1 = 0;
    for(int i = c; string[i] != '\0'; i++){
        nomeClube[c1] = string[i];
        c1++;
    }
    nomeClube[c1-1] = '\0';
    
    //Armazena o id e a idade
    if(verifica_se_eh_numero(id[0])){ 
        registro.id = captura_id_e_idade(id);
    }
    else{
        registro.id = -1;
    }
    //printf("idade) %d %s\n", (int) strlen(token), token);

    if(verifica_se_eh_numero(idade[0])){ 
        registro.idade = captura_id_e_idade(idade);
    }
    else{ 
        registro.idade = -1;
    }

    //Armazena o tamanho do nome do jogador e o nome do jogador
    if(strlen(nomeJog) > 1){
        registro.tamNomeJog = (int) strlen(nomeJog);
        strcpy(registro.nomeJogador, nomeJog);
    }
    else{
        registro.tamNomeJog = 0;
    }

    //Armazena o tamanho da string "nacionalidade" e a nacionalidade
    if(strlen(nacionalidade) > 1){
        registro.tamNacionalidade = (int)strlen(nacionalidade);
        strcpy(registro.nacionalidade, nacionalidade);
    }
    else{
        registro.tamNacionalidade = 0;
    }

    //Armazena o tamanho da string "nomeClube" e o nome do clube
    if(strlen(nomeClube) > 1){
        registro.tamNomeClube = (int)strlen(nomeClube);
        strcpy(registro.nomeClube, nomeClube);
    }
    else{
        registro.tamNomeClube = 0;
    }

    printf("%d ", registro.tamNomeClube);
    printf("%s \n", registro.nomeClube);

    return registro;
}

//Função para encontrar o valor númerico do id e da id
int captura_id_e_idade(char *string_de_numeros){
    int casa_decimal = 1;
    int numero_inteiro = 0;

    for(int i = 0; i < strlen(string_de_numeros) - 1; i++){
        casa_decimal = casa_decimal * 10;
    }

    for(int i = 0; i < strlen(string_de_numeros); i++){
        numero_inteiro += converte_string_em_numero(string_de_numeros[i]) * casa_decimal;
        casa_decimal = casa_decimal / 10;
    }
    return numero_inteiro;
}
//Função que converte um char em int
int converte_string_em_numero(char string){
    return (int) string - 48;
}
//Função que verifica se um valor é char ou int
int verifica_se_eh_numero(char string){
    char numeros[11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};

    for(int i = 0; numeros[i] != '\0'; i++){
        if(string == numeros[i]) return 1;
    }

    return 0;
}
//Função para descobrir o tamanho do registro
int retorna_tamanho_reg(REGISTRO_DADOS registro){
    int tamanho = 0;
    tamanho  = sizeof(char); //removido
    tamanho += sizeof(int);  //tamanhoRegistro
    tamanho += sizeof(long int); //prox
    tamanho += sizeof(int); //id
    tamanho += sizeof(int); //idade
    tamanho += sizeof(int); //tamNomeJog


    //Somando o valor do tamanho dos campos variáveis
    if(registro.tamNomeJog != 0){
        tamanho += sizeof(char) * registro.tamNomeJog;
    }

    tamanho += sizeof(int); //tamNacionalidade

    
    if(registro.tamNacionalidade != 0){
        tamanho += sizeof(char) * registro.tamNacionalidade;
    }
    
    tamanho += sizeof(int); //tamNomeClube
    
    if(registro.tamNomeClube != 0){
        tamanho += sizeof(char) * registro.tamNomeClube;
    }

    return tamanho;
}
//Função que imprime os registros salvos no arquivo binário
void recuperacao_dados(FILE *arq){

    REGISTRO_CABECA c;

    int conta_reg = 0;

    REGISTRO_DADOS d;

    // Lendo as inforacoes do cabecalho
    fread(&c.status, sizeof(char), 1, arq);
    fread(&c.topo, sizeof(long int), 1, arq);
    fread(&c.proxByteOffset, sizeof(long int), 1, arq);
    fread(&c.nroRegArq, sizeof(int), 1, arq);
    fread(&c.nroRegRem, sizeof(int), 1, arq);


    // Caso não existam registros
    if(c.nroRegArq == 0) _erros(2);
 
    //Laço para imprimir os registros
    while(conta_reg < c.nroRegArq){
        fread(&d.removido, sizeof(char), 1, arq);
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

        if(d.removido == '0'){
            imprime_registros(d.tamNomeJog, d.tamNacionalidade, d.tamNomeClube, d.nomeJogador, d.nacionalidade, d.nomeClube);
        }

        conta_reg++;
    }
}
