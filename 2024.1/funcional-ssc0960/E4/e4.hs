main :: IO ()
main = do
    pins <- readPins
    putStrLn (scoreTable pins 0 ++ show (pointCounter pins 0))

readPins :: IO [Int]
readPins = fmap (map read.words) getLine

pointCounter :: (Eq a, Num a) => [a] -> a -> a
pointCounter [] frame = 0
pointCounter [a] frame = a
pointCounter [a,b,c] frame = if frame==9 then a+b+c else a+2*(b+c)
pointCounter [a,b] frame = a+b
pointCounter (a:b:c:t) frame
    | a==10 = sum [a,b,c] + pointCounter (b:c:t) (frame+1)
    | a+b==10 = sum [a,b,c] + pointCounter (c:t) (frame+1)
    | otherwise = sum [a,b] + pointCounter (c:t) (frame+1)


scoreTable :: (Eq a, Num a, Show a) => [a] -> a -> String
scoreTable [] frame = " "
scoreTable [a,b,c] frame
    | frame==9 && a==10 && b==10 && c==10 = "X X X | "
    | frame==9 && a==10 && b==10 = "X X " ++ show c ++ " | "
    | frame==9 && a==10 && b+c==10 = "X " ++ show b ++ " / | "
    | frame==9 && a==10 = "X " ++ show b ++ " " ++ show c ++ " | "
    | frame==9 && a+b==10 && c== 10 = show a ++ " / X | "
    | frame==9 = show a ++ " / " ++ show c ++ " | "
    | otherwise = "X _ | " ++ scoreTable [b,c] frame
scoreTable [a,b] frame
    | a+b==10 = show a ++ " / | "
    | otherwise = show a ++ " " ++ show b ++ " | "
scoreTable (a:b:t) frame
    | a==10 = "X _ | " ++ scoreTable (b:t) (frame+1)
    | otherwise = scoreTable [a,b] frame ++ scoreTable t  (frame+1)
scoreTable [a] frame = " "