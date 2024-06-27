import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import java.util.Comparator;

import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;



public class Main {
    static class CountryData {
        String country;
        int confirmed;
        int deaths;
        int recovery;
        int active;

        private CountryData(String country, int confirmed, int deaths, int recovery, int active) {
            this.country = country;
            this.confirmed = confirmed;
            this.deaths = deaths;
            this.recovery = recovery;
            this.active = active;
        }

        static CountryData fromCsvLine(String line) {
            String[] parts = line.split(",");
            return new CountryData(
                    parts[0],
                    Integer.parseInt(parts[1]),
                    Integer.parseInt(parts[2]),
                    Integer.parseInt(parts[3]),
                    Integer.parseInt(parts[4])

            );
        }
    }

    public static void main(String[] args) throws IOException {
        try (// Lendo input
             Scanner scanner = new Scanner(System.in)) {
            String[] inputParts = scanner.nextLine().split(" ");
            int n1 = Integer.parseInt(inputParts[0]);
            int n2 = Integer.parseInt(inputParts[1]);
            int n3 = Integer.parseInt(inputParts[2]);
            int n4 = Integer.parseInt(inputParts[3]);


            // Lendo dados, processando e salvando em uma lista
            List<CountryData> countryDataList = Files.lines(Paths.get("dados.csv"))
                    .map(CountryData::fromCsvLine)
                    .collect(Collectors.toList());

            // Soma de "Active" dos países com "Confirmed" >= n1
            int sumActiveConfirmed = countryDataList.stream()
                    .filter(cd -> cd.confirmed >= n1)
                    .mapToInt(cd -> cd.active)
                    .sum();

            System.out.println(sumActiveConfirmed);

            //Soma de "Deaths" dos n3 países com menores valores de "Confirmed" dentre os n2 com maiores valores de "Active"
            int sumDeaths = countryDataList.stream()
                    .sorted(Comparator.comparingInt(cd -> -cd.active)) // ordena por Active decrescente
                    .limit(n2)
                    .sorted(Comparator.comparingInt(cd -> cd.confirmed)) // ordena por Confirmed crescente
                    .limit(n3)
                    .mapToInt(cd -> cd.deaths)
                    .sum();

            System.out.println(sumDeaths);

            // Top n4 paises com maior valor de "Confirmed" em ordem alfabética
            List<String> topNConfirmedCountries = countryDataList.stream()
                    .sorted(Comparator.comparingInt(cd -> -cd.confirmed)) // ordena por Confirmed decrescente
                    .limit(n4)
                    .map(cd -> cd.country)
                    .sorted()
                    .collect(Collectors.toList());

            topNConfirmedCountries.forEach(System.out::println);

        } catch (NumberFormatException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}

