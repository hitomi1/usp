import math


# Função para calcular a distância euclidiana entre dois pontos
def distancia(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)


# Função de divisão e conquista para encontrar a menor distância
def menor_distancia_dividir_conquistar(pontos):
    if len(pontos) <= 3:
        # Caso base: calcular a distância por força bruta
        min_dist = float("inf")
        for i in range(len(pontos)):
            for j in range(i + 1, len(pontos)):
                min_dist = min(min_dist, distancia(pontos[i], pontos[j]))
        return min_dist

    # Dividir em duas metades
    meio = len(pontos) // 2
    ponto_meio = pontos[meio]

    # Menor distância nas duas metades
    d_esquerda = menor_distancia_dividir_conquistar(pontos[:meio])
    d_direita = menor_distancia_dividir_conquistar(pontos[meio:])
    d_min = min(d_esquerda, d_direita)

    # Verificar a menor distância na faixa que cruza a linha divisória
    faixa = []
    for p in pontos:
        if abs(p[0] - ponto_meio[0]) < d_min:
            faixa.append(p)

    # Ordenar pela coordenada y
    faixa.sort(key=lambda p: p[1])

    # Comparar cada ponto da faixa com seus vizinhos próximos
    for i in range(len(faixa)):
        for j in range(i + 1, len(faixa)):
            if faixa[j][1] - faixa[i][1] >= d_min:
                break
            d_min = min(d_min, distancia(faixa[i], faixa[j]))

    return d_min


# Função principal para encontrar a menor distância
def menor_distancia(pontos):
    # Ordenar pela coordenada x
    pontos.sort()
    return menor_distancia_dividir_conquistar(pontos)


# Leitura da entrada
n = int(input())
pontos = []
for _ in range(n):
    x, y = map(int, input().split())
    pontos.append((x, y))

# Encontrar e imprimir a menor distância com duas casas decimais
resultado = menor_distancia(pontos)
print(f"{resultado:.2f}")
