def is_prime(num):
    def check_prime(n, i):
        if i * i > n:
            return True
        if n % i == 0:
            return False
        return check_prime(n, i + 1)
    
    if num < 2:
        return False
    return check_prime(num, 2)

def prime_intervals(X, Y):
    def find_primes(x, y):
        return [i for i in range(x, y + 1) if is_prime(i)]
    
    def calculate_intervals(primes):
        return [primes[i+1] - primes[i] for i in range(len(primes) - 1)]
    
    primes = find_primes(X, Y)
    intervals = calculate_intervals(primes)
    return max(intervals) if intervals else 0


X = int(input())
Y = int(input())
result = prime_intervals(X, Y)
print(result)