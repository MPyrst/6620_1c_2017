#include "sorters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
#define LONGEST_LINE 1000
#define WORD_SEPARATORS "\r\t\n \r\n" //Separadores: Tab, nueva linea, y espacio en blanco.
typedef int bool;

int amountOfWordsInFile(FILE *inputFile);

//Imprime una palabra por linea
void printArray(char *arrayWords[], int amountOfWords);
void freeArray(char *arrayWords[], int amountOfWords);

int main() {
	bool useBubbleSort = true;

	FILE *inputFile;
	inputFile = fopen("lorem", "r");

	int amountOfWords = amountOfWordsInFile(inputFile);
    char *arrayOfWords[amountOfWords];

    //Leo de nuevo sabiendo el tamaño del vector
    rewind(inputFile);
	int i = 0;
	char *cp, *bp;
	char line[LONGEST_LINE];
	while (fgets(line, sizeof(line), inputFile) != NULL) {
        bp = line;
		while (1) {
			cp = strtok(bp, WORD_SEPARATORS);
			bp = NULL;
			if (cp == NULL)
                break;

			int wordLength = strlen(cp);
			char *ptr = malloc(wordLength);
			int z;
			for(z = 0; z <= wordLength-1; z++){
				ptr[z]=cp[z];
			}
			arrayOfWords[i] =ptr;
			//printf("palabra: %s\n",arrayOfWords[i]);
			i++;
		}
	}
	fclose(inputFile);

	if (useBubbleSort == true)
		bubbleSort(arrayOfWords,amountOfWords);
	else
		quickSort(arrayOfWords,amountOfWords);

	printArray(arrayOfWords, amountOfWords);
	freeArray(arrayOfWords, amountOfWords);
	return 0;
}

void printArray(char *arrayOfWords[], int amountOfWords){
    int i;
    for(i = 0; i <= amountOfWords-1; i++){
        if (arrayOfWords[i] != NULL)
            printf("%s\n",arrayOfWords[i]);
    }
}

int amountOfWordsInFile(FILE *inputFile){
    rewind(inputFile);
    int amountOfWords=0;

	char *cp, *bp;
	char line[LONGEST_LINE ];

	while (fgets(line, sizeof(line), inputFile) != NULL) {
        bp = line;
		while (1) {
            //Separadores: Tab, nueva linea, y espacio en blanco.
			cp = strtok(bp, WORD_SEPARATORS);
			bp = NULL;
			if (cp == NULL)
                break;
			amountOfWords++;
		}
	}
	return amountOfWords;
}

void freeArray(char *arrayWords[], int amountOfWords){
	int i = 0;
	for(i = 0; i <= amountOfWords-1; i++){
		free(arrayWords[i]);
	}
}


