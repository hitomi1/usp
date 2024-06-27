# Variáveis com os arquivos que serão usados
OBJS = func_uteis.o ler_escrever_arqs.o lista_ligada.o main.o
LIBRARY = minhabiblioteca.so

# Regra para compilar o executável principal
all: $(OBJS)
	@gcc -g $(OBJS) -o main

# Regra para criar a biblioteca compartilhada
shared: $(OBJS)
	@gcc -shared -fPIC -o $(LIBRARY) $(OBJS)

# Regras para compilar cada arquivo .o individualmente
func_uteis.o:
	@gcc -c func_uteis.c -fPIC

ler_escrever_arqs.o:
	@gcc -c ler_escrever_arqs.c -fPIC

lista_ligada.o:
	@gcc -c lista_ligada.c -fPIC

main.o:
	@gcc -c main.c -fPIC

# Alvo para rodar o programa
run:
	@./main

# Alvo para limpar arquivos gerados
clean:
	@rm -rf *.o main $(LIBRARY) *~

# Alvo para criar um arquivo zip com os arquivos fonte e Makefile
zip:
	zip -r main *.c *.h *.dat *.csv Makefile
