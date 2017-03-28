#include "sorters.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#define true 1
#define false 0
#define LONGEST_LINE 1000
/************************************************************************************/
/* Que les parecen??? WORD_SEPARATORS "\" .,;:¿?'¡!—-_·&*#\n\r\t\f\v()[]{}~%<>|"    */
/************************************************************************************/
#define WORD_SEPARATORS "\r\t\n \r\n" //Separadores: Tab, nueva linea, y espacio en blanco.
typedef int bool;
bool useBubbleSort = true;
bool haveQuickSort = false;
bool haveBubbleSort = false;

int amountOfWordsInFile(FILE *inputFile);

//Imprime una palabra por linea
void printArray(char *arrayWords[], int amountOfWords, char *input);

void freeArray(char *arrayWords[], int amountOfWords);

void printError(char *message);

int main(int argc, char *argv[]) {
    int parameter;
    char *input = NULL;
    char *output = NULL;

    static struct option long_options[] =
        {
            /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"version", no_argument, 0, 'V'},
          {"help",   no_argument,0, 'h'},
          {"output", required_argument, 0, 'o'},
          {"input",  required_argument, 0, 'i'},
          {"qsort",  no_argument, 0, 'q'},
          {"bsort",  no_argument, 0, 'b'},
          {0, 0, 0, 0}
        };

   opterr = 0;
   int option_index = 0;

    while ((parameter = getopt_long(argc, argv, "Vhqb:o:i:",
                       long_options, &option_index)) != -1)
        switch (parameter) {
            case 'V':
                printf("This is version 1.0 from tpo: Basic infrastructure.\n");
                exit(EXIT_FAILURE);
            case 'h':
                printf( "Usage:\n"
                            " tp0 -h\n"
                            " tp0 -V\n"
                            " tp0 [options] file\n"
                        "Options:\n"
                            " -V, --version print version and quit.\n"
                            " -h, --help Print this information.\n"
                            " -o, --output Path to output file.\n"
                            " -i, --intput Path to input file.\n"
                            " -q, --qsort Use quicksort.\n"
                            " -b, --bsort Use bubblesort.");
                exit(EXIT_FAILURE);
            case 'o':
                output = optarg;
                break;
            case 'i':
                input = optarg;
                break;
            case 'q':
                useBubbleSort = false;
                haveQuickSort = true;
                break;
            case 'b':
                useBubbleSort = true;
                haveBubbleSort = true;
                break;
            case '?':
                if (optopt == 'o' || optopt == 'i') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if (isprint (optopt)) {
                    fprintf(stderr, "Unknown argument '-%c'.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);

                }
                exit(EXIT_FAILURE);
            default:
                exit(EXIT_FAILURE);
        }

    if (haveBubbleSort && haveQuickSort) {
        printError("fatal: cannot use quicksort and bubblesort at the same time.");
        exit(EXIT_FAILURE);
     }

     FILE *inputFile;

     /* ouptut value */
    if (input != NULL) {
        inputFile = fopen(input, "r");
        if (inputFile == NULL) {
            printError("fatal: cannot open input file.");
            exit(EXIT_FAILURE);
        }
    }

     FILE *outputFile;

    /* ouptut value */
    if (output != NULL) {
        outputFile = fopen(output, "w");
        if (outputFile == NULL) {
            printError("fatal: cannot open output file.");
            exit(EXIT_FAILURE);
        }
    } else {//stdout
        outputFile = stdout;
    }

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

    printArray(arrayOfWords, amountOfWords, input);
    freeArray(arrayOfWords, amountOfWords);
    return 0;
}

void printArray(char *arrayOfWords[], int amountOfWords, char *input) {
    int i;
    for (i = 0; i <= amountOfWords - 1; i++) {
        printf("(%s)\n", arrayOfWords[i]);
    }

    printf("\nArchivo %s\n", input);
}


void freeArray(char *arrayWords[], int amountOfWords) {
    int i = 0;
    for (i = 0; i <= amountOfWords - 1; i++) {
        free(arrayWords[i]);
    }
    free(arrayWords);
}

void printError(char *message) { fprintf(stderr, "%s\n", message); }
