isPrime :: Int -> Bool
isPrime num
    | num < 2 = False
    | otherwise = all (\x -> num `mod` x /= 0) [2..floor (sqrt (fromIntegral num))]

primesInRange :: Int -> Int -> [Int]
primesInRange x y = filter isPrime [x..y]

primeIntervals :: Int -> Int -> Int
primeIntervals x y
    | null primes = 0
    | otherwise   = maximum intervals
    where
        primes = primesInRange x y
        intervals = zipWith (-) (tail primes) primes

main :: IO ()
main = do
    xStr <- getLine
    yStr <- getLine
    let x = read xStr :: Int
        y = read yStr :: Int
    print (primeIntervals x y)
