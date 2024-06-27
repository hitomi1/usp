import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

import java.util.*;

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
            List<CountryData> countryDataList = new ArrayList<>();
            List<String> lines = Files.readAllLines(Paths.get("dados.csv"));
            for (int i = 0; i < lines.size(); i++) {
                countryDataList.add(CountryData.fromCsvLine(lines.get(i)));
            }

            // Soma de "Active" dos países com "Confirmed" >= n1
            int sumActiveConfirmed = 0;
            for (CountryData cd : countryDataList) {
                if (cd.confirmed >= n1) {
                    sumActiveConfirmed += cd.active;
                }
            }

            System.out.println(sumActiveConfirmed);

            //Soma de "Deaths" dos n3 países com menores valores de "Confirmed" dentre os n2 com maiores valores de "Active"
            List<CountryData> topNActive = new ArrayList<>(countryDataList);
            Collections.sort(topNActive, new Comparator<CountryData>() {
                public int compare(CountryData cd1, CountryData cd2) {
                    return Integer.compare(cd2.active, cd1.active);
                }
            });

            if (n2 > topNActive.size()) n2 = topNActive.size();
            List<CountryData> topNConfirmedInTopNActive = new ArrayList<>();
            for (int i = 0; i < n2; i++) {
                topNConfirmedInTopNActive.add(topNActive.get(i));
            }

            Collections.sort(topNConfirmedInTopNActive, new Comparator<CountryData>() {
                public int compare(CountryData cd1, CountryData cd2) {
                    return Integer.compare(cd1.confirmed, cd2.confirmed);
                }
            });

            if (n3 > topNConfirmedInTopNActive.size()) n3 = topNConfirmedInTopNActive.size();
            int sumDeaths = 0;
            for (int i = 0; i < n3; i++) {
                sumDeaths += topNConfirmedInTopNActive.get(i).deaths;
            }
            System.out.println(sumDeaths);

            // Top n4 paises com maior valor de "Confirmed" em ordem alfabética
            List<CountryData> topNConfirmed = new ArrayList<>(countryDataList);
            Collections.sort(topNConfirmed, new Comparator<CountryData>() {
                public int compare(CountryData cd1, CountryData cd2) {
                    return Integer.compare(cd2.confirmed, cd1.confirmed);
                }
            });

            if (n4 > topNConfirmed.size()) n4 = topNConfirmed.size();
            List<String> topNConfirmedCountries = new ArrayList<>();
            for (int i = 0; i < n4; i++) {
                topNConfirmedCountries.add(topNConfirmed.get(i).country);
            }
            Collections.sort(topNConfirmedCountries);

            topNConfirmedCountries.forEach(System.out::println);

        } catch (NumberFormatException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}

