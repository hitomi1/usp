# Nome do compilador
CC = gcc

# Opções de compilação: -fopenmp é necessário para suportar OpenMP
CFLAGS = -fopenmp

# Nome do arquivo executável

EXEC = main

# Arquivos fonte
SRC = e1.c

# Regra padrão: compilar o programa

all: $(EXEC)

# Regra para compilar o programa usando OpenMP

$(EXEC): $(SRC)

	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)


# Regra para limpar arquivos objeto e executáveis
clean:
	rm -f $(EXEC)

# Regra para compilar e executar o programa
run: $(EXEC)
	./$(EXEC)

