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
	if (argc <= 1 ){
		printf("Error: No se indicó archivo.\n");
		return 1;
	}

	//Por defecto se usa Bubblesort, salvo especificado en los argumentos
	//Refactorizar con getopt
	if( (argv[2] != NULL) && (strcmp(argv[2],"-q") == 0)){
		useBubbleSort = false;
	}

	FILE *inputFile;
	inputFile = fopen(argv[1], "r");

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

	if (useBubbleSort)
		bubbleSort(arrayOfWords,amountOfWords);
	else
		quickSort(arrayOfWords,amountOfWords);

	printArray(arrayOfWords, amountOfWords, argv);
	freeArray(arrayOfWords, amountOfWords);
	return 0;
}

void printArray(char *arrayOfWords[], int amountOfWords, char *argv[]){
    int i;
    for(i = 0; i <= amountOfWords-1; i++){
        if (arrayOfWords[i] != NULL)
            printf("%s\n",arrayOfWords[i]);
    }
    printf("\nArchivo %s\n", argv[1]);
    printf("%s #Compares: %llu\n",(useBubbleSort) ? "Bubblesort ":"Quicksort", getComparesCount());
    printf("%s #Swaps: %llu\n",(useBubbleSort) ? "Bubblesort ":"Quicksort", getSwapsCount());
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


