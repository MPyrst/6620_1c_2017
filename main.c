#include "sorters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONGEST_LINE 1000

int amountOfWordsInFile(FILE *inputFile);
void printArray(char *arrayWords[], int amountOfWords);


int main() {
	FILE *inputFile;
	inputFile = fopen("lorem", "r");
	int amountOfWords= amountOfWordsInFile(inputFile);

    char *arrayOfWords[amountOfWords];

    //Leo de nuevo sabiendo el tamaño del vector
    rewind(inputFile);
	int i=0;
	char *cp, *bp;
	char line[LONGEST_LINE];
	while (fgets(line, sizeof(line), inputFile) != NULL) {
        bp = line;
		while (1) {
            //Separadores: Tab, nueva linea, y espacio en blanco.
			cp = strtok(bp, "\t\n ");
			bp = NULL;
			if (cp == NULL)
                break;

			arrayOfWords[i++] = cp;
		}
	}
	fclose(inputFile);

	bubbleSort(arrayOfWords,amountOfWords);
	quickSort(arrayOfWords,amountOfWords);
	printArray(arrayOfWords, amountOfWords);
 return 0;
}

void printArray(char *arrayOfWords[], int amountOfWords){
    int i;
    for(i = 0; i <= amountOfWords-1; i++){
        if (arrayOfWords[i] != NULL)
            printf("Imprimiendo: %s\n",arrayOfWords[i]);
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
			cp = strtok(bp, "\t\n ");
			bp = NULL;
			if (cp == NULL)
                break;
			amountOfWords++;
		}
	}
	return amountOfWords;
}


