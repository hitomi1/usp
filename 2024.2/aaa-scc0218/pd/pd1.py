def min_cost(n, d):
    dp = [0] * n
    dp[0] = 0
    dp[1] = abs(d[1] - d[0])

    for i in range(2, n):
        dp[i] = min(dp[i - 1] + abs(d[i] - d[i - 1]), dp[i - 2] + abs(d[i] - d[i - 2]))

    return dp[-1]


n = int(input())
d = list(map(int, input().split()))
print(min_cost(n, d))
