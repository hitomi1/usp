def verifica(paginas, n, m, limite):
    estudantes = 1
    paginas_atual = 0
    
    for i in range(n):
        if paginas_atual + paginas[i] > limite:
            estudantes += 1
            paginas_atual = paginas[i]
            if estudantes > m:
                return False
        else:
            paginas_atual += paginas[i]
    
    return True

def alocar_livros(paginas, n, m):
    if m > n:
        return -1
    
    limite_min = max(paginas)
    limite_max = sum(paginas)
    resultado = limite_max
    
    while limite_min <= limite_max:
        meio = (limite_min + limite_max) // 2
        
        if verifica(paginas, n, m, meio):
            resultado = meio
            limite_max = meio - 1
        else:
            limite_min = meio + 1
    
    return resultado

# Leitura da entrada
n, m = map(int, input().split())
paginas = list(map(int, input().split()))

# Encontrar e imprimir o resultado
resultado = alocar_livros(paginas, n, m)
print(resultado)
