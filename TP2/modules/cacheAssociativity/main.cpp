#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

void cacheAssociativity(register unsigned int n,
                        char *array, unsigned int waySize) {
    register unsigned int j = 0;
    for (j = 0; j < n; j++) {
        *(array + j * waySize) = 'E';
    }
}


int main(int argc, char *argv[]) {
    unsigned int blockSize = (unsigned int) std::stoul(argv[1]);
    unsigned int cacheSize = (unsigned int) std::stoul(argv[2]);
    unsigned int n = (unsigned int) std::stoul(argv[3]);


    register unsigned int i = 0;
    char *array = (char *) malloc(cacheSize);

    register unsigned int blocksQuantity = cacheSize / blockSize / n;

    register unsigned int iterations = 0;

    register unsigned int j = 0;
    unsigned int waySize = cacheSize / n;

    for (iterations = 0; iterations < 100; iterations++) {
        for (i = 0; i < blocksQuantity; i++) {//blocks along same way
            for (j = 0; j < n; j++) {//#n ways
                *(array + i * blockSize + j * waySize) = 'D';
                /*cout << "i: " << i << " j: " << j << " BlockSize: " << blockSize << "Dir:" <<
                *(i * blockSize + j * n + array) << endl;*/
            }
        }
    }

    cacheAssociativity(n, array, waySize);

    delete[] array;

    return EXIT_SUCCESS;
}

