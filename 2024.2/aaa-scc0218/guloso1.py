def trocas(v, n):
    rounds = 0
    target = 1

    while target <= n:
        rounds += 1
        for x in v:
            if target == x:
                target += 1
    print(rounds)


n = int(input())
vetor = list(map(int, input().strip().split()))

trocas(vetor, n)
