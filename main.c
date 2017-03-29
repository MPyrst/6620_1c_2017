#include "sorters.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>

#define true 1
#define false 0
#define LONGEST_LINE 1024
/************************************************************************************/
/* Que les parecen??? WORD_SEPARATORS "\" .,;:¿?'¡!—-_·&*#\n\r\t\f\v()[]{}~%<>|"    */
/************************************************************************************/
#define WORD_SEPARATORS "\r\t\n \r\n" //Separadores: Tab, nueva linea, y espacio en blanco.
typedef int bool;
bool useBubbleSort = true;
bool haveQuickSort = false;
bool haveBubbleSort = false;

void freeArray(char *wordsArray[], unsigned int amountOfWords);

void printArray(char *arrayWords[], unsigned int amountOfWords, FILE *outputStream);

void closeFile(FILE *inputFile);

void printError(char *message);

int main(int argc, char *argv[]) {
    int parameter;
    char *input = NULL;
    char *output = NULL;

    static struct option long_options[] =
    {
    /* These options don’t set a flag.
     We distinguish them by their indices. */
    {"version", no_argument,       0, 'V'},
    {"help",    no_argument,       0, 'h'},
    {"output",  required_argument, 0, 'o'},
    {"input",   required_argument, 0, 'i'},
    {"qsort",   no_argument,       0, 'q'},
    {"bsort",   no_argument,       0, 'b'},
    {0, 0,                         0, 0}
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
                printf("Usage:\n"
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

    FILE *inputStream = NULL;
    FILE *outputStream = NULL;

    /* input value */
    if (input != NULL) {
        inputStream = fopen(input, "r");
        if (inputStream != NULL) {
            struct stat st;
            if (stat(input, &st) != 0) {
                printError("Invalid input file.\n");
                return EXIT_FAILURE;
            } else if (st.st_size == 0) {
                printError("Empty input file.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            printError("fatal: cannot open input file.");
            exit(EXIT_FAILURE);
        }
    }

/* ouptut value */
    if (output != NULL) {
        outputStream = fopen(output, "w");
        if (outputStream == NULL) {
            printError("fatal: cannot open output file.");
            closeFile(inputStream);
            exit(EXIT_FAILURE);
        }
    }

    char **wordsArray = NULL;


    unsigned int amountOfWords = 0L;
    char *token;
    char line[LONGEST_LINE];
    while (fgets(line, sizeof(line), inputStream) != NULL) {

        token = strtok(line, WORD_SEPARATORS);
/* walk through other tokens */
        while (token != NULL) {
            size_t wordLength = strlen(token);
            char *word = malloc(sizeof(char) * (wordLength + 1));

            if (word == NULL) {
                printError("fatal: Malloc failed");
                fclose(inputStream);
                fclose(outputStream);
                freeArray(wordsArray, amountOfWords
                );
                exit(EXIT_FAILURE);
            }

            strcpy(word, token
            );
            wordsArray = realloc(wordsArray, (amountOfWords + 1) * sizeof(char *));

            if (wordsArray == NULL) {
                printError("fatal: Malloc failed");
                fclose(inputStream);
                fclose(outputStream);
                freeArray(wordsArray, amountOfWords
                );
                exit(EXIT_FAILURE);
            }

            wordsArray[amountOfWords] = word;
            //printf("Palabra: %s\n", wordsArray[amountOfWords]);
            amountOfWords++;
            token = strtok(NULL, WORD_SEPARATORS);
        }
    }

    //printf("Amount of words: %u\n", amountOfWords);
    closeFile(inputStream);

    if (useBubbleSort) {
        bubbleSort(wordsArray, amountOfWords
        );
    } else {
        quickSort(wordsArray, amountOfWords
        );
    }

    printArray(wordsArray, amountOfWords, outputStream);
    freeArray(wordsArray, amountOfWords);
    closeFile(outputStream);
    return EXIT_SUCCESS;
}

void freeArray(char *wordsArray[], unsigned int amountOfWords) {

    if (amountOfWords == 0) {
        return;
    }

    unsigned int i;
    for (i = 0; i <= amountOfWords - 1; i++) {
        free(wordsArray[i]);
    }

    free(wordsArray);
}

void printArray(char *wordsArray[], unsigned int amountOfWords, FILE *outputStream) {

    if (amountOfWords == 0) {
        return;
    }

    FILE *out = outputStream;

    if (out == NULL) {
        out = stdout;
    }

    printf("\n%d\n", amountOfWords);

    unsigned int i;
    for (i = 0; i <= amountOfWords - 1; i++) {
        fprintf(out, "%s\n", wordsArray[i]);
    }
}

void closeFile(FILE *file) {
    if (file != NULL) {
        fclose(file);
    }
}


void printError(char *message) { fputs(message, stderr); }
