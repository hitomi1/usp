import Data.List (sortBy, sortOn)
import Data.Ord (comparing)
import System.IO

type CountryData = (String, Int, Int, Int, Int)

-- Essa função deve receber o caminho de um arquivo e retornar uma lista de tuplas com os dados dos países
readCSVFile :: FilePath -> IO [CountryData]
readCSVFile path = do
  file <- openFile path ReadMode
  contents <- hGetContents file

-- Chama a função readLines para cada linha do arquivo usando um map
  return $ map readLines $ lines contents

-- Função que lê uma linha e retorna uma tupla com os dados do país
readLines :: String -> CountryData
readLines line = case splitString line of
  [country, confirmed, deaths, recovery, active] -> (country, read confirmed, read deaths, read recovery, read active)

-- Função que divide uma string por vírgulas
splitString :: String -> [String]
splitString [] = [""]
splitString (delimiter : next)
  | delimiter == ',' = "" : rest
  | otherwise = (delimiter : head rest) : tail rest
  where
    rest = splitString next

main :: IO ()
main = do
  -- Leitura dos valores n1, n2, n3 e n4
    input <- getLine
    let [n1, n2, n3, n4] = map read $ words input :: [Int]

    countryData <- readCSVFile "dados.csv"

    -- Processando os dados
    let sumActiveConfirmed = sum [active | (_, confirmed, _, _, active) <- countryData, confirmed >= n1]
    putStrLn $ show sumActiveConfirmed

    let topNActive = take n2 $ sortBy (flip $ comparing (\(_, _, _, _, active) -> active)) countryData
    let sortedByConfirmed = sortOn (\(_, confirmed, _, _, _) -> confirmed) topNActive
    let sumDeaths = sum [deaths | (_, _, deaths, _, _) <- take n3 sortedByConfirmed]
    putStrLn $ show sumDeaths

    let topNConfirmed = take n4 $ sortBy (flip $ comparing (\(_, confirmed, _, _, _) -> confirmed)) countryData
    let sortedByName = sortOn (\(country, _, _, _, _) -> country) topNConfirmed
    mapM_ (putStrLn . (\(country, _, _, _, _) -> country)) sortedByName
