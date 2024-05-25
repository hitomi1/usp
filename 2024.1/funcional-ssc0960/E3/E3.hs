-- Função principal que recebe uma lista de inteiros e retorna o comprimento do maior segmento crescente
maxCrescentSegmentLength :: [Int] -> Int
maxCrescentSegmentLength [] = 0
maxCrescentSegmentLength [x] = 1
maxCrescentSegmentLength (x:xs) = maxSegmentLength xs x 1 1
  where
    -- Função auxiliar para iterar pela lista e encontrar o maior segmento crescente
    maxSegmentLength :: [Int] -> Int -> Int -> Int -> Int
    maxSegmentLength [] _ currentMax globalMax = max currentMax globalMax
    maxSegmentLength (y:ys) prev currentMax globalMax
      | y > prev  = maxSegmentLength ys y (currentMax + 1) globalMax
      | otherwise = maxSegmentLength ys y 1 (max currentMax globalMax)

-- Função para leitura de uma lista de inteiros a partir da entrada padrão
readInts :: IO [Int]
readInts = fmap (map read . words) getLine

main :: IO ()
main = do
    -- putStrLn "Digite uma lista de números inteiros, separados por espaços:"
    inputList <- readInts
    let result = maxCrescentSegmentLength inputList
    print result
