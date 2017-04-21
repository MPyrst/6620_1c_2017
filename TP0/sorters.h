#ifndef SORTERS_H_INCLUDED
#define SORTERS_H_INCLUDED

void bubbleSort(char *arrayOfWords[], unsigned int arraySize);

void quickSort(char *arrayOfWords[], unsigned int arraySize);

int compare(char *word1, char *word2);

void swap(char *arrayOfWords[], unsigned int position1, unsigned int position2);

#endif // SORTERS_H_INCLUDED
