#ifndef SORTERS_H_INCLUDED
#define SORTERS_H_INCLUDED
void bubbleSort(char *arrayOfWords[], int arraySize);
void quickSort(char *arrayOfWords[], int arraySize);
int compare(char *word1, char*word2);
void swap(char *arrayOfWords[], int position1, int position2);
int getSwapsCount();
int getComparesCount();
#endif // SORTERS_H_INCLUDED
