# Interface Gráfico para Manipular Registro de Jogadores


## Alunos
- Breno Rodrigues - 11734142
- Gustavo Hitomi - 11801202
- Murilo Matos - 13719065

## Uso

- `make all` no arquivo Makefile da pasta c_files
- Executar o server em Python
- `python3 client_socket.py`
- Executar a interface gráfica em Java
- `javac FIFAFileLoaderGUI.java`
- `java FIFAFileLoaderGUI`


### 1. Estrutura do Projeto
Diretórios e Arquivos Principais

FIFAFileLoaderGUI: Contém todo o código-fonte Java e a interface gráfica.

c_files/client_socket.py: Contém o código-fonte do servidor em Python.

c_files/: Contém o código-fonte C para manipulação dos arquivos indexados.

### 2. Dependências
Biblioteca de interface gráfica Swing.
Biblioteca para comunicação Java Networking
### 3. Interface Gráfica
Opção para carregar arquivos FIFA (binario1 a binario10).

Campos de Texto:
- ID (int)
- Idade (int)
- Nome do Jogador (String)
- Nacionalidade (String)
- Nome do Clube (String)
  
Botão "Buscar":
Realiza a busca e exibe a lista de jogadores que correspondem aos critérios.

Botão "Remover":
Permite remover o jogador do arquivo.

Botão "Alterar":
Permite alterar os atributos do jogador.

### 4. Implementação do Servidor em Python
#### Estrutura do Servidor Python
`client_socket.py`: Configuração e gerenciamento do servidor socket.

####  Dependências
- Biblioteca socket do Python.

- Biblioteca subprocess para executar a função `main` em C.

#### Lógica do Servidor

- Iniciar o Servidor: Configura o servidor para escutar conexões.

- Receber Comandos: Recebe comandos da GUI.

- Comunicação com Programa C:

- Passa dados via STDIN

- Responder à GUI: Envia resultados de volta para a GUI.


### 5. Fluxo de Trabalho
#### Carregando um Arquivo

- O usuário seleciona um arquivo no menu da GUI.

- A GUI envia um comando para o servidor Python.

- O servidor Python chama a função C para carregar o arquivo.

#### Buscando Jogadores

- O usuário preenche os campos de texto e clica em "Buscar".

- A GUI envia os critérios de busca para o servidor.

- O servidor processa a busca e retorna os resultados.

### 6. Conclusão
Essa abordagem garante que todas as funcionalidades especificadas sejam implementadas de maneira organizada e modular. Com essa estrutura, cada parte do projeto (Java, Python, C) pode ser desenvolvida, testada e mantida independentemente, facilitando o desenvolvimento colaborativo e a integração final.