#include "sorters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define LONGEST_LINE 1000
#define WORD_SEPARATORS "\r\t\n \r\n" //Separadores: Tab, nueva linea, y espacio en blanco.
typedef int bool;
bool useBubbleSort = true;

int amountOfWordsInFile(FILE *inputFile);

//Imprime una palabra por linea
void printArray(char *arrayWords[], int amountOfWords, char *argv[]);

void freeArray(char *arrayWords[], int amountOfWords);

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Error: No se indicó archivo.\n");
        return 1;
    }

    //Por defecto se usa Bubblesort, salvo especificado en los argumentos
    //Refactorizar con getopt
    if ((argv[2] != NULL) && (strcmp(argv[2], "-q") == 0)) {
        useBubbleSort = false;
    }

    FILE *inputFile;
    inputFile = fopen(argv[1], "r");
    char **arrayOfWords = NULL;

    rewind(inputFile);
    int amountOfWords = 0;
    char *cp, *bp;
    char line[LONGEST_LINE];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        bp = line;
        while (1) {
            cp = strtok(bp, WORD_SEPARATORS);
            bp = NULL;
            if (cp == NULL)
                break;

            size_t wordLength = strlen(cp);
            char *ptr = malloc(sizeof(char) * (wordLength + 1));
            strcpy(ptr, cp);

            arrayOfWords = realloc(arrayOfWords, (amountOfWords + 1) * sizeof(char *));
            arrayOfWords[amountOfWords] = ptr;
            //printf("palabra: %s\n", arrayOfWords[amountOfWords]);

            amountOfWords++;
        }
    }

    printf("Amount of words: %d", amountOfWords);
    fclose(inputFile);

    if (useBubbleSort) {
        bubbleSort(arrayOfWords, amountOfWords);
    } else {
        quickSort(arrayOfWords, amountOfWords);
    }

    printArray(arrayOfWords, amountOfWords, argv);
    freeArray(arrayOfWords, amountOfWords);
    return 0;
}

void printArray(char *arrayOfWords[], int amountOfWords, char *argv[]) {
    int i;
    for (i = 0; i <= amountOfWords - 1; i++) {
        printf("(%s)\n", arrayOfWords[i]);
    }

    printf("\nArchivo %s\n", argv[1]);
}


void freeArray(char *arrayWords[], int amountOfWords) {
    int i = 0;
    for (i = 0; i <= amountOfWords - 1; i++) {
        free(arrayWords[i]);
    }
    free(arrayWords);
}


