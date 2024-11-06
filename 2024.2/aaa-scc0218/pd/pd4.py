def max_pages(n, x, prices, pages):
    dp = [0] * (x + 1)

    for i in range(n):
        for j in range(x, prices[i] - 1, -1):
            dp[j] = max(dp[j], dp[j - prices[i]] + pages[i])

    return dp[x]


n, x = map(int, input().split())
prices = list(map(int, input().split()))
pages = list(map(int, input().split()))

print(max_pages(n, x, prices, pages))
