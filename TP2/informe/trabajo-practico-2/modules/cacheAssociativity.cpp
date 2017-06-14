#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

void cacheAssociativity(register unsigned int n,
                        char *array, unsigned int cacheSize) {
    register unsigned int i = 0;
    for (i = 0; i < n; i++) {
        *(array + i * cacheSize) = 'E';
    }
}


int main(int argc, char *argv[]) {
    unsigned int blockSize = (unsigned int) std::stoul(argv[1]);
    unsigned int cacheSize = (unsigned int) std::stoul(argv[2]);
    unsigned int n = (unsigned int) std::stoul(argv[3]);

    register unsigned int i = 0;
    char *array = (char *) malloc(cacheSize * n);

    if (array == NULL) {
        fprintf(stderr, "Too big malloc of: %d", cacheSize * n);
        exit(EXIT_FAILURE);
    }

    register unsigned int iterations = 0;

    for (iterations = 0; iterations < 100; iterations++) {
        for (i = 0; i < n; i++) {//#n ways
            *(array + i * cacheSize) = 'D';
        }
    }

    cacheAssociativity(n, array, cacheSize);

    delete[] array;

    return EXIT_SUCCESS;
}

