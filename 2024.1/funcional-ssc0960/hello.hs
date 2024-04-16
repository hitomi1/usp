soma :: Int -> Int -> Int
soma x y = x+y

lerNumero :: IO Int
lerNumero = do
    input <- getLine
    case reads input of
        [(numero, "")] -> return numero
        _ -> do
            putStrLn "Por favor, insira um número válido."
            lerNumero

-- Exemplo de uso das funções
main :: IO ()
main = do
    -- num1 <- read <$> getLine :: IO Int
    num1 <- lerNumero 
    -- num2 <- read <$> getLine :: IO Int
    num2 <- lerNumero 

    let resultado = soma num1 num2
    print resultado