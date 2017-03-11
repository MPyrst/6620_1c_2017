#include "sorters.h"
#include <string.h>

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

void quickSort(char *arrayOfWords[], int arraySize){

}
