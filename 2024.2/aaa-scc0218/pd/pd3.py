MOD = 10**9 + 7


def count_paths(n, grid):
    dp = [[0] * n for _ in range(n)]

    if grid[0][0] == ".":
        dp[0][0] = 1

    for i in range(n):
        for j in range(n):
            if grid[i][j] == "*":
                dp[i][j] = 0

            else:
                if i > 0:
                    dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD  # Caminho de cima
                if j > 0:
                    dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD  # Caminho da esquerda
                if i > 0 and j > 0:
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD

    return dp[n - 1][n - 1]


n = int(input())
grid = [input().strip() for _ in range(n)]

print(count_paths(n, grid))
