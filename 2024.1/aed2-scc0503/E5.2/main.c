#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ISBN_LENGTH 14
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHORS_LENGTH 100
#define MAX_GENRE_LENGTH 50
#define MAX_MAGAZINE_LENGTH 50
#define MAX_PUBLISHER_LENGTH 50
#define MAX_VOLUMES 200

typedef struct {
    char isbn[MAX_ISBN_LENGTH];
    char title[MAX_TITLE_LENGTH];
    char authors[MAX_AUTHORS_LENGTH];
    int startYear;
    int endYear;
    char genre[MAX_GENRE_LENGTH];
    char magazine[MAX_MAGAZINE_LENGTH];
    char publisher[MAX_PUBLISHER_LENGTH];
    int editionYear;
    int volumeCount;
    int acquiredVolumeCount;
    int acquiredVolumes[MAX_VOLUMES];
} Manga;

Manga mangas[MAX_VOLUMES];
int mangaCount = 0;

typedef struct {
    char isbn[MAX_ISBN_LENGTH];
    int index;
} PrimaryIndex;

PrimaryIndex primaryIndex[MAX_VOLUMES];
int primaryIndexCount = 0;

typedef struct {
    char title[MAX_TITLE_LENGTH];
    int indices[MAX_VOLUMES];
    int count;
} SecondaryIndex;

SecondaryIndex secondaryIndex[MAX_VOLUMES];
int secondaryIndexCount = 0;

void saveMangas() {
    FILE *file = fopen("mangas.txt", "w");
    if (!file) {
        perror("Failed to open mangas file for writing");
        return;
    }
    for (int i = 0; i < mangaCount; i++) {
        Manga *manga = &mangas[i];
        fprintf(file, "%s\n%s\n%s\n%d %d\n%s\n%s\n%s\n%d %d %d\n", manga->isbn,
                manga->title, manga->authors, manga->startYear, manga->endYear,
                manga->genre, manga->magazine, manga->publisher,
                manga->editionYear, manga->volumeCount,
                manga->acquiredVolumeCount);
        for (int j = 0; j < manga->acquiredVolumeCount; j++) {
            fprintf(file, "%d", manga->acquiredVolumes[j]);
            if (j < manga->acquiredVolumeCount - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void loadMangas() {
    FILE *file = fopen("mangas.txt", "r");
    if (!file) {
        perror("Failed to open mangas file for reading");
        return;
    }
    while (fscanf(file, "%s\n", mangas[mangaCount].isbn) != EOF) {
        fgets(mangas[mangaCount].title, MAX_TITLE_LENGTH, file);
        mangas[mangaCount].title[strcspn(mangas[mangaCount].title, "\n")] = 0;
        fgets(mangas[mangaCount].authors, MAX_AUTHORS_LENGTH, file);
        mangas[mangaCount].authors[strcspn(mangas[mangaCount].authors, "\n")] =
            0;
        fscanf(file, "%d %d\n", &mangas[mangaCount].startYear,
               &mangas[mangaCount].endYear);
        fgets(mangas[mangaCount].genre, MAX_GENRE_LENGTH, file);
        mangas[mangaCount].genre[strcspn(mangas[mangaCount].genre, "\n")] = 0;
        fgets(mangas[mangaCount].magazine, MAX_MAGAZINE_LENGTH, file);
        mangas[mangaCount]
            .magazine[strcspn(mangas[mangaCount].magazine, "\n")] = 0;
        fgets(mangas[mangaCount].publisher, MAX_PUBLISHER_LENGTH, file);
        mangas[mangaCount]
            .publisher[strcspn(mangas[mangaCount].publisher, "\n")] = 0;
        fscanf(file, "%d %d %d\n", &mangas[mangaCount].editionYear,
               &mangas[mangaCount].volumeCount,
               &mangas[mangaCount].acquiredVolumeCount);
        for (int i = 0; i < mangas[mangaCount].acquiredVolumeCount; i++) {
            fscanf(file, "%d", &mangas[mangaCount].acquiredVolumes[i]);
            if (i < mangas[mangaCount].acquiredVolumeCount - 1) {
                fgetc(file);
            }
        }
        fgetc(file);  // Read the newline character
        mangaCount++;
    }
    fclose(file);
}

void saveIndexes() {
    FILE *file = fopen("primaryIndex.txt", "w");
    if (!file) {
        perror("Failed to open primary index file for writing");
        return;
    }
    for (int i = 0; i < primaryIndexCount; i++) {
        fprintf(file, "%s %d\n", primaryIndex[i].isbn, primaryIndex[i].index);
    }
    fclose(file);

    file = fopen("secondaryIndex.txt", "w");
    if (!file) {
        perror("Failed to open secondary index file for writing");
        return;
    }
    for (int i = 0; i < secondaryIndexCount; i++) {
        fprintf(file, "%s", secondaryIndex[i].title);
        for (int j = 0; j < secondaryIndex[i].count; j++) {
            fprintf(file, " %d", secondaryIndex[i].indices[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void loadIndexes() {
    FILE *file = fopen("primaryIndex.txt", "r");
    if (!file) {
        perror("Failed to open primary index file for reading");
        return;
    }
    while (fscanf(file, "%s %d\n", primaryIndex[primaryIndexCount].isbn,
                  &primaryIndex[primaryIndexCount].index) != EOF) {
        primaryIndexCount++;
    }
    fclose(file);

    file = fopen("secondaryIndex.txt", "r");
    if (!file) {
        perror("Failed to open secondary index file for reading");
        return;
    }
    while (fscanf(file, "%s", secondaryIndex[secondaryIndexCount].title) !=
           EOF) {
        secondaryIndex[secondaryIndexCount].count = 0;
        int index;
        while (fscanf(file, "%d", &index) != EOF) {
            secondaryIndex[secondaryIndexCount]
                .indices[secondaryIndex[secondaryIndexCount].count++] = index;
            if (fgetc(file) == '\n') {
                break;
            }
        }
        secondaryIndexCount++;
    }
    fclose(file);
}

void createManga() {
    Manga manga;
    printf("Enter ISBN: ");
    scanf("%s", manga.isbn);

    for (int i = 0; i < primaryIndexCount; i++) {
        if (strcmp(primaryIndex[i].isbn, manga.isbn) == 0) {
            printf("\nISBN already exists.\n\n");
            return;
        }
    }

    printf("Enter title: ");
    scanf(" %[^\n]", manga.title);
    printf("Enter authors: ");
    scanf(" %[^\n]", manga.authors);
    printf("Enter start year: ");
    while (scanf("%d", &manga.startYear) != 1 || manga.startYear <= 0) {
        printf("Invalid start year. Enter a valid year: ");
        scanf("%*s");
    }
    printf("Enter end year: ");
    while (scanf("%d", &manga.endYear) != 1 ||
           manga.endYear < manga.startYear) {
        printf("Invalid end year. Enter a valid year: ");
        scanf("%*s");
    }
    printf("Enter genre: ");
    scanf(" %[^\n]", manga.genre);
    printf("Enter magazine: ");
    scanf(" %[^\n]", manga.magazine);
    printf("Enter publisher: ");
    scanf(" %[^\n]", manga.publisher);
    printf("Enter edition year: ");
    while (scanf("%d", &manga.editionYear) != 1 || manga.editionYear <= 0) {
        printf("Invalid edition year. Enter a valid year: ");
        scanf("%*s");
    }
    printf("Enter volume count: ");
    while (scanf("%d", &manga.volumeCount) != 1 || manga.volumeCount <= 0) {
        printf("Invalid volume count. Enter a positive integer: ");
        scanf("%*s");
    }
    printf("Enter acquired volume count: ");
    while (scanf("%d", &manga.acquiredVolumeCount) != 1 ||
           manga.acquiredVolumeCount < 0 ||
           manga.acquiredVolumeCount > manga.volumeCount) {
        printf("Invalid acquired volume count. Enter a valid number: ");
        scanf("%*s");
    }
    printf("Enter acquired volumes: ");
    for (int i = 0; i < manga.acquiredVolumeCount; i++) {
        while (scanf("%d", &manga.acquiredVolumes[i]) != 1 ||
               manga.acquiredVolumes[i] <= 0 ||
               manga.acquiredVolumes[i] > manga.volumeCount) {
            printf("Invalid volume number. Enter a valid number: ");
            scanf("%*s");
        }
    }

    mangas[mangaCount++] = manga;
    primaryIndex[primaryIndexCount].index = mangaCount - 1;
    strcpy(primaryIndex[primaryIndexCount++].isbn, manga.isbn);

    int found = 0;
    for (int i = 0; i < secondaryIndexCount; i++) {
        if (strcmp(secondaryIndex[i].title, manga.title) == 0) {
            secondaryIndex[i].indices[secondaryIndex[i].count++] =
                mangaCount - 1;
            found = 1;
            break;
        }
    }
    if (!found) {
        strcpy(secondaryIndex[secondaryIndexCount].title, manga.title);
        secondaryIndex[secondaryIndexCount].indices[0] = mangaCount - 1;
        secondaryIndex[secondaryIndexCount++].count = 1;
    }

    saveMangas();
    saveIndexes();
    printf("\nManga added successfully.\n\n");
}

void listMangas() {
    for (int i = 0; i < mangaCount; i++) {
        Manga *manga = &mangas[i];
        printf(
            "ISBN: %s\nTitle: %s\nAuthors: %s\nStart Year: %d\nEnd Year: "
            "%d\nGenre: %s\nMagazine: %s\nPublisher: %s\nEdition Year: "
            "%d\nVolume Count: %d\nAcquired Volume Count: %d\nAcquired "
            "Volumes: ",
            manga->isbn, manga->title, manga->authors, manga->startYear,
            manga->endYear, manga->genre, manga->magazine, manga->publisher,
            manga->editionYear, manga->volumeCount, manga->acquiredVolumeCount);
        for (int j = 0; j < manga->acquiredVolumeCount; j++) {
            printf("%d", manga->acquiredVolumes[j]);
            if (j < manga->acquiredVolumeCount - 1) {
                printf(",");
            }
        }
        printf("\n\n");
    }
}

void updateManga() {
    char isbn[MAX_ISBN_LENGTH];
    printf("Enter ISBN of the manga to update: ");
    scanf("%s", isbn);

    int found = 0;
    for (int i = 0; i < mangaCount; i++) {
        if (strcmp(mangas[i].isbn, isbn) == 0) {
            found = 1;
            printf("Enter new title: ");
            scanf(" %[^\n]", mangas[i].title);
            printf("Enter new authors: ");
            scanf(" %[^\n]", mangas[i].authors);
            printf("Enter new start year: ");
            while (scanf("%d", &mangas[i].startYear) != 1 ||
                   mangas[i].startYear <= 0) {
                printf("Invalid start year. Enter a valid year: ");
                scanf("%*s");
            }
            printf("Enter new end year: ");
            while (scanf("%d", &mangas[i].endYear) != 1 ||
                   mangas[i].endYear < mangas[i].startYear) {
                printf("Invalid end year. Enter a valid year: ");
                scanf("%*s");
            }
            printf("Enter new genre: ");
            scanf(" %[^\n]", mangas[i].genre);
            printf("Enter new magazine: ");
            scanf(" %[^\n]", mangas[i].magazine);
            printf("Enter new publisher: ");
            scanf(" %[^\n]", mangas[i].publisher);
            printf("Enter new edition year: ");
            while (scanf("%d", &mangas[i].editionYear) != 1 ||
                   mangas[i].editionYear <= 0) {
                printf("Invalid edition year. Enter a valid year: ");
                scanf("%*s");
            }
            printf("Enter new volume count: ");
            while (scanf("%d", &mangas[i].volumeCount) != 1 ||
                   mangas[i].volumeCount <= 0) {
                printf("Invalid volume count. Enter a positive integer: ");
                scanf("%*s");
            }
            printf("Enter new acquired volume count: ");
            while (scanf("%d", &mangas[i].acquiredVolumeCount) != 1 ||
                   mangas[i].acquiredVolumeCount < 0 ||
                   mangas[i].acquiredVolumeCount > mangas[i].volumeCount) {
                printf("Invalid acquired volume count. Enter a valid number: ");
                scanf("%*s");
            }
            printf("Enter new acquired volumes: ");
            for (int j = 0; j < mangas[i].acquiredVolumeCount; j++) {
                while (scanf("%d", &mangas[i].acquiredVolumes[j]) != 1 ||
                       mangas[i].acquiredVolumes[j] <= 0 ||
                       mangas[i].acquiredVolumes[j] > mangas[i].volumeCount) {
                    printf("Invalid volume number. Enter a valid number: ");
                    scanf("%*s");
                }
            }
            printf("\nManga updated successfully.\n\n");
            break;
        }
    }
    if (!found) {
        printf("\nManga with ISBN %s not found.\n\n", isbn);
    }
    saveMangas();
    saveIndexes();
}

void deleteManga() {
    char isbn[MAX_ISBN_LENGTH];
    printf("Enter ISBN of the manga to delete: ");
    scanf("%s", isbn);

    int found = 0;
    for (int i = 0; i < mangaCount; i++) {
        if (strcmp(mangas[i].isbn, isbn) == 0) {
            found = 1;
            for (int j = i; j < mangaCount - 1; j++) {
                mangas[j] = mangas[j + 1];
            }
            mangaCount--;

            for (int j = 0; j < primaryIndexCount; j++) {
                if (strcmp(primaryIndex[j].isbn, isbn) == 0) {
                    for (int k = j; k < primaryIndexCount - 1; k++) {
                        primaryIndex[k] = primaryIndex[k + 1];
                    }
                    primaryIndexCount--;
                    break;
                }
            }

            for (int j = 0; j < secondaryIndexCount; j++) {
                for (int k = 0; k < secondaryIndex[j].count; k++) {
                    if (secondaryIndex[j].indices[k] == i) {
                        for (int l = k; l < secondaryIndex[j].count - 1; l++) {
                            secondaryIndex[j].indices[l] =
                                secondaryIndex[j].indices[l + 1];
                        }
                        secondaryIndex[j].count--;
                        break;
                    }
                }
                if (secondaryIndex[j].count == 0) {
                    for (int k = j; k < secondaryIndexCount - 1; k++) {
                        secondaryIndex[k] = secondaryIndex[k + 1];
                    }
                    secondaryIndexCount--;
                    break;
                }
            }
            break;
        }
    }
    if (!found) {
        printf("\nManga with ISBN %s not found.\n\n", isbn);
    } else {
        printf("\nManga deleted successfully.\n\n");
        saveMangas();
        saveIndexes();
    }
}

int main() {
    loadMangas();
    loadIndexes();

    int choice;
    while (1) {
        printf(
            "1. Add Manga\n2. List Mangas\n3. Update Manga\n4. Delete "
            "Manga\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createManga();
                break;
            case 2:
                listMangas();
                break;
            case 3:
                updateManga();
                break;
            case 4:
                deleteManga();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
