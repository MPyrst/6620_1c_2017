#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LONGEST_LINE 1000

int amountOfWordsInFile(FILE *inputFile);
void printArray(char *arrayWords[], int amountOfWords);
void bubbleSort(char *arrayOfWords[], int arraySize);
int compare(char *word1, char*word2);
void swap(char *arrayOfWords[], int position1, int position2);

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
	//quickSort(arrayOfWords,amountOfWords);
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

void bubbleSort(char *arrayOfWords[], int arraySize){
    int i, j;
    for(i=0; i<arraySize; i++) {
        for(j=0; j<arraySize-1; j++) {
            if(compare(arrayOfWords[j], arrayOfWords[j+1]) > 0) {
                swap(arrayOfWords, j, j+1);
            }
        }
    }
}

int compare(char *word1, char*word2){
    int cmp = strcmp(word1,word2);
    return cmp;
}

void swap(char *arrayOfWords[], int position1, int position2){
    char *auxPtr = arrayOfWords[position2];
    arrayOfWords[position2] = arrayOfWords[position1];
    arrayOfWords[position1] = auxPtr;
}
