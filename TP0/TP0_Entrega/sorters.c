#include "sorters.h"
#include <string.h>

#define true 1
#define false 0
typedef int bool;

void bubbleSort(char *arrayOfWords[], unsigned int length) {
    unsigned int i, j;
    for (i = 0; i < length; i++) {
        bool swapped = false;
        for (j = 0; j < length - i - 1; j++) {
            if (compare(arrayOfWords[j], arrayOfWords[j + 1]) > 0) {
                swapped = true;
                swap(arrayOfWords, j, j + 1);
            }
        }
        //Mejora: Deja de comparar si esta ordenado
        if (!swapped) {
            break;
        }
    }
}

int compare(char *word1, char *word2) {
    return strcmp(word1, word2);
}

void swap(char *arrayOfWords[], unsigned int position1, unsigned int position2) {
    char *auxPtr = arrayOfWords[position2];
    arrayOfWords[position2] = arrayOfWords[position1];
    arrayOfWords[position1] = auxPtr;
}

void quickSort(char *arrayOfWords[], unsigned int length) {
    unsigned int i, pivot = 0;

    if (length <= 1) {
        return;
    }

    // swap a randomly selected value to the last node
    //swap(arrayOfWords, arrayOfWords+((unsigned int)rand() % length), arrayOfWords+length-1);
    // reset the pivot index to zero, then scan
    for (i = 0; i < length - 1; ++i) {
        if (compare(arrayOfWords[i], arrayOfWords[length - 1]) < 0) {
            swap(arrayOfWords, i, pivot++);
        }
    }

    // move the pivot value into its place
    swap(arrayOfWords, pivot, length - 1);

    // and invoke on the subsequences. does NOT include the pivot-slot
    quickSort(arrayOfWords, pivot++);
    quickSort(arrayOfWords + pivot, length - pivot);
}
