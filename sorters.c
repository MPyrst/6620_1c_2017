#include "sorters.h"
#include <string.h>

void bubbleSort(char *arrayOfWords[], int length){
    int i, j;
    for(i=0; i<length; i++) {
        for(j=0; j<length-i-1; j++) {
            if(compare(arrayOfWords[j], arrayOfWords[j+1]) > 0) {
                swap(arrayOfWords, j, j+1);
            }
        }
    }
}

int compare(char *word1, char *word2){
    int cmp = strcmp(word1,word2);
    return cmp;
}

void swap(char *arrayOfWords[], int position1, int position2){
    char *auxPtr = arrayOfWords[position2];
    arrayOfWords[position2] = arrayOfWords[position1];
    arrayOfWords[position1] = auxPtr;
}

void quickSort(char *arrayOfWords[], int length){
	unsigned int i, pivot=0;

    if (length <= 1)
        return;

    // swap a randomly selected value to the last node
    //swap(arrayOfWords, arrayOfWords+((unsigned int)rand() % length), arrayOfWords+length-1);

    // reset the pivot index to zero, then scan
    for (i=0 ; i < length-1; ++i) {
        //if (strcmp(arrayOfWords[i], arrayOfWords[length-1]) < 0)
        if (compare(arrayOfWords[i], arrayOfWords[length-1]) < 0)
            swap(arrayOfWords, i, pivot++);
    }

    // move the pivot value into its place
    swap(arrayOfWords, pivot, length-1);

    // and invoke on the subsequences. does NOT include the pivot-slot
    quickSort(arrayOfWords, pivot++);
    quickSort(arrayOfWords + pivot, length - pivot);
}
