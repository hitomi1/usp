T = int(input())

for case in range(1, T + 1):
    N = int(input())
    temas = {}

    for _ in range(N):
        entrada = input().split()
        tema = entrada[0]

        dias = int(entrada[1])
        temas[tema] = dias

    D = int(input())
    tema_pedido = input().strip()

    if tema_pedido not in temas:
        print(f"Case {case}: Deu ruim! Va trabalhar")
    elif temas[tema_pedido] <= D:
        print(f"Case {case}: Ufa!")
    elif D < temas[tema_pedido] <= D + 5:
        print(f"Case {case}: Atrasado")

    else:
        print(f"Case {case}: Deu ruim! Va trabalhar")
