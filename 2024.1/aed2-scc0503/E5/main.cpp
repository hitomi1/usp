#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 100
#define MAX_GENRE_LEN 50
#define MAX_MAGAZINE_LEN 50
#define MAX_PUBLISHER_LEN 50
#define MAX_VOLUMES 150

class Manga {
public:
    std::string ISBN;
    std::string title;
    std::string authors;
    int startYear;
    int endYear;
    std::string genre;
    std::string magazine;
    std::string publisher;
    int editionYear;
    int totalVolumes;
    int acquiredVolumes;
    std::vector<int> volumes;

    // Manga() : startYear(0), endYear(0), editionYear(0), totalVolumes(0), acquiredVolumes(0) {}

    void input() {
        std::cout << "Enter ISBN: ";
        std::getline(std::cin, ISBN);

        std::cout << "Enter title: ";
        std::getline(std::cin, title);

        std::cout << "Enter authors: ";
        std::getline(std::cin, authors);

        std::cout << "Enter start year: ";
        std::cin >> startYear;

        std::cout << "Enter end year: ";
        std::cin >> endYear;
        std::cin.ignore();

        std::cout << "Enter genre: ";
        std::getline(std::cin, genre);

        std::cout << "Enter magazine: ";
        std::getline(std::cin, magazine);

        std::cout << "Enter publisher: ";
        std::getline(std::cin, publisher);

        std::cout << "Enter edition year: ";
        std::cin >> editionYear;

        std::cout << "Enter total volumes: ";
        std::cin >> totalVolumes;

        std::cout << "Enter acquired volumes: ";
        std::cin >> acquiredVolumes;

        volumes.resize(acquiredVolumes);
        std::cout << "Enter list of acquired volumes (space separated): ";
        for (int i = 0; i < acquiredVolumes; ++i) {
            std::cin >> volumes[i];
        }
        std::cin.ignore();
    }

    void display() const {
        std::cout << "ISBN: " << ISBN << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Authors: " << authors << std::endl;
        std::cout << "Start Year: " << startYear << std::endl;
        std::cout << "End Year: " << endYear << std::endl;
        std::cout << "Genre: " << genre << std::endl;
        std::cout << "Magazine: " << magazine << std::endl;
        std::cout << "Publisher: " << publisher << std::endl;
        std::cout << "Edition Year: " << editionYear << std::endl;
        std::cout << "Total Volumes: " << totalVolumes << std::endl;
        std::cout << "Acquired Volumes: " << acquiredVolumes << std::endl;
        std::cout << "List of Acquired Volumes: ";
        for (int i = 0; i < acquiredVolumes; ++i) {
            std::cout << volumes[i] << " ";
        }
        std::cout << std::endl;
    }

    std::string to_string() const {
        std::string result;
        result += ISBN + "|" + title + "|" + authors + "|" + std::to_string(startYear) + "|" + std::to_string(endYear) + "|" +
                  genre + "|" + magazine + "|" + publisher + "|" + std::to_string(editionYear) + "|" +
                  std::to_string(totalVolumes) + "|" + std::to_string(acquiredVolumes) + "|";
        for (int i = 0; i < acquiredVolumes; ++i) {
            result += std::to_string(volumes[i]) + (i == acquiredVolumes - 1 ? "" : ",");
        }
        return result;
    }

    void from_string(const std::string &str) {
        std::istringstream ss(str);
        std::getline(ss, ISBN, '|');
        std::getline(ss, title, '|');
        std::getline(ss, authors, '|');
        ss >> startYear;
        ss.ignore();
        ss >> endYear;
        ss.ignore();
        std::getline(ss, genre, '|');
        std::getline(ss, magazine, '|');
        std::getline(ss, publisher, '|');
        ss >> editionYear;
        ss.ignore();
        ss >> totalVolumes;
        ss.ignore();
        ss >> acquiredVolumes;
        ss.ignore();
        volumes.resize(acquiredVolumes);
        for (int i = 0; i < acquiredVolumes; ++i) {
            ss >> volumes[i];
            if (ss.peek() == ',') ss.ignore();
        }
    }
};

struct PrimaryIndex {
    std::string ISBN;
    int position;
};

struct SecondaryIndex {
    std::string title;
    std::string ISBN;
};

class MangaDB {
private:
    std::vector<PrimaryIndex> primaryIndex;
    std::vector<SecondaryIndex> secondaryIndex;

    std::fstream dataFile;
    std::fstream primaryIndexFile;
    std::fstream secondaryIndexFile;

public:
    MangaDB() {
        dataFile.open("manga.txt", std::ios::in | std::ios::out | std::ios::app);
        primaryIndexFile.open("primary_index.txt", std::ios::in | std::ios::out | std::ios::app);
        secondaryIndexFile.open("secondary_index.txt", std::ios::in | std::ios::out | std::ios::app);

        loadIndexes();
    }

    ~MangaDB() {
        dataFile.close();
        primaryIndexFile.close();
        secondaryIndexFile.close();
    }

    void createManga() {
        Manga manga;
        manga.input();
        int position = static_cast<int>(primaryIndex.size());

        dataFile.seekp(0, std::ios::end);
        dataFile << manga.to_string() << std::endl;

        addPrimaryIndex(manga.ISBN, position);
        addSecondaryIndex(manga.title, manga.ISBN);

        std::cout << "Manga created successfully!" << std::endl;
    }

    void readManga() {
        std::cout << "Enter ISBN to read: ";
        std::string ISBN;
        std::cin >> ISBN;

        int index = searchPrimaryIndex(ISBN);
        if (index != -1) {
            Manga manga;
            readRecord(index, manga);
            manga.display();
        } else {
            std::cout << "Manga not found!" << std::endl;
        }
    }

    void updateManga() {
        std::cout << "Enter ISBN to update: ";
        std::string ISBN;
        std::cin >> ISBN;

        int index = searchPrimaryIndex(ISBN);
        if (index != -1) {
            Manga manga;
            readRecord(index, manga);
            manga.display();

            std::cout << "Enter new details:" << std::endl;
            manga.input();

            updateRecord(index, manga);

            std::cout << "Manga updated successfully!" << std::endl;
        } else {
            std::cout << "Manga not found!" << std::endl;
        }
    }

    void deleteManga() {
        std::cout << "Enter ISBN to delete: ";
        std::string ISBN;
        std::cin >> ISBN;

        int index = searchPrimaryIndex(ISBN);
        if (index != -1) {
            std::cout << "Are you sure you want to delete this manga? (y/n): ";
            char choice;
            std::cin >> choice;

            if (choice == 'y' || choice == 'Y') {
                deleteRecord(index);
                removePrimaryIndex(ISBN);
                removeSecondaryIndex(ISBN);

                std::cout << "Manga deleted successfully!" << std::endl;
            }
        } else {
            std::cout << "Manga not found!" << std::endl;
        }
    }

private:
    void loadIndexes() {
        primaryIndexFile.seekg(0, std::ios::beg);
        secondaryIndexFile.seekg(0, std::ios::beg);

        std::string line;
        while (std::getline(primaryIndexFile, line)) {
            PrimaryIndex pIndex;
            std::istringstream ss(line);
            ss >> pIndex.ISBN >> pIndex.position;
            primaryIndex.push_back(pIndex);
        }

        while (std::getline(secondaryIndexFile, line)) {
            SecondaryIndex sIndex;
            std::istringstream ss(line);
            std::getline(ss, sIndex.title, '|');
            ss >> sIndex.ISBN;
            secondaryIndex.push_back(sIndex);
        }
    }

    void addPrimaryIndex(const std::string &ISBN, int position) {
        PrimaryIndex index = {ISBN, position};
        primaryIndex.push_back(index);

        primaryIndexFile.seekp(0, std::ios::end);
        primaryIndexFile << ISBN << " " << position << std::endl;
    }

    void addSecondaryIndex(const std::string &title, const std::string &ISBN) {
        SecondaryIndex index = {title, ISBN};
        secondaryIndex.push_back(index);

        secondaryIndexFile.seekp(0, std::ios::end);
        secondaryIndexFile << title << "|" << ISBN << std::endl;
    }

    void removePrimaryIndex(const std::string &ISBN) {
        primaryIndex.erase(std::remove_if(primaryIndex.begin(), primaryIndex.end(),
                                           [&ISBN](const PrimaryIndex &index) { return index.ISBN == ISBN; }),
                            primaryIndex.end());

        // Rewrite the primary index file
        primaryIndexFile.close();
        primaryIndexFile.open("primary_index.txt", std::ios::out | std::ios::trunc);
        for (const auto &index : primaryIndex) {
            primaryIndexFile << index.ISBN << " " << index.position << std::endl;
        }
        primaryIndexFile.close();
        primaryIndexFile.open("primary_index.txt", std::ios::in | std::ios::out | std::ios::app);
    }

    void removeSecondaryIndex(const std::string &ISBN) {
        secondaryIndex.erase(std::remove_if(secondaryIndex.begin(), secondaryIndex.end(),
                                             [&ISBN](const SecondaryIndex &index) { return index.ISBN == ISBN; }),
                              secondaryIndex.end());

        // Rewrite the secondary index file
        secondaryIndexFile.close();
        secondaryIndexFile.open("secondary_index.txt", std::ios::out | std::ios::trunc);
        for (const auto &index : secondaryIndex) {
            secondaryIndexFile << index.title << "|" << index.ISBN << std::endl;
        }
        secondaryIndexFile.close();
        secondaryIndexFile.open("secondary_index.txt", std::ios::in | std::ios::out | std::ios::app);
    }

    int searchPrimaryIndex(const std::string &ISBN) {
        for (size_t i = 0; i < primaryIndex.size(); ++i) {
            if (primaryIndex[i].ISBN == ISBN) {
                return primaryIndex[i].position;
            }
        }
        return -1; // Not found
    }

    int searchSecondaryIndex(const std::string &title) {
        for (size_t i = 0; i < secondaryIndex.size(); ++i) {
            if (secondaryIndex[i].title == title) {
                return searchPrimaryIndex(secondaryIndex[i].ISBN);
            }
        }
        return -1; // Not found
    }

    void readRecord(int index, Manga &manga) {
        dataFile.seekg(0, std::ios::beg);
        for (int i = 0; i < index; ++i) {
            std::string line;
            std::getline(dataFile, line);
        }
        std::string record;
        std::getline(dataFile, record);

        manga.from_string(record);
    }

    void updateRecord(int index, const Manga &manga) {
        dataFile.seekp(0, std::ios::beg);
        for (int i = 0; i < index; ++i) {
            std::string line;
            std::getline(dataFile, line);
        }
        dataFile << manga.to_string() << std::endl;
    }

    void deleteRecord(int index) {
        std::fstream tempFile("temp.txt", std::ios::out);
        dataFile.seekg(0, std::ios::beg);
        for (int i = 0; i < index; ++i) {
            std::string line;
            std::getline(dataFile, line);
            tempFile << line << std::endl;
        }
        std::string line;
        std::getline(dataFile, line); // Skip the record to be deleted
        while (std::getline(dataFile, line)) {
            tempFile << line << std::endl;
        }
        tempFile.close();
        dataFile.close();

        // Rename temp file to data file
        std::remove("manga.txt");
        std::rename("temp.txt", "manga.txt");

        dataFile.open("manga.txt", std::ios::in | std::ios::out | std::ios::app);
    }
};

int main() {
    MangaDB db;

    while (true) {
        std::cout << "Menu:\n"
                     "1. Create Manga\n"
                     "2. Read Manga\n"
                     "3. Update Manga\n"
                     "4. Delete Manga\n"
                     "5. Exit\n"
                     "Choose an option: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                db.createManga();
                break;
            case 2:
                db.readManga();
                break;
            case 3:
                db.updateManga();
                break;
            case 4:
                db.deleteManga();
                break;
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
