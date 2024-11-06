def max_cost(tasks):
    tasks.sort()
    current_time = 0
    total_cost = 0

    for t, d in tasks:
        end_time = current_time + t
        total_cost += d - end_time
        current_time = end_time

    return total_cost

# Leitura da entrada
n = int(input())
tasks = []
for _ in range(n):
    t, d = map(int, input().split())
    tasks.append((t, d))

# Chamada da função e impressão do resultado
print(max_cost(tasks))
