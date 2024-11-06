def min_jumps(n, m):
    dp = [float("inf")] * n
    dp[0] = 0

    for i in range(n):
        if dp[i] == float("inf"):
            continue

        for j in range(i + 1, min(i + m[i] + 1, n)):
            dp[j] = min(dp[j], dp[i] + 1)

    if dp[n - 1] == float("inf"):
        return "Salto impossivel"
    else:
        return dp[n - 1]


n = int(input())
m = list(map(int, input().split()))

print(min_jumps(n, m))
