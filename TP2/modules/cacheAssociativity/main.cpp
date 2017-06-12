#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

void cacheAssociativity(register unsigned int n,
                        char *array) {
    register unsigned int j = 0;
    for (j = 0; j < n; j++) {
        *(array + j * n) = 'E';
    }
}


int main(int argc, char *argv[]) {
    unsigned int blockSize = (unsigned int) std::stoul(argv[1]);
    unsigned int cacheSize = (unsigned int) std::stoul(argv[2]);
    unsigned int n = (unsigned int) std::stoul(argv[3]);


    register unsigned int i = 0;
    char **array = new char *[n];
    for (i = 0; i < n; i++) {
        array[i] = new char[cacheSize / n];
    }

    register unsigned int iterations = 0;
    register unsigned int blocksQuantity = cacheSize / blockSize / n;

    register unsigned int j = 0;

    for (iterations = 0; iterations < 100; iterations++) {
        for (i = 0; i < blocksQuantity; i++) {//blocks along same way
            for (j = 0; j < n; j++) {//#n ways
                array[j][i * blockSize] = 'F';
                //cout << "Pos:" << array + j + i * blockSize << endl;
            }
        }
    }

    cacheAssociativity(n, *array);

    for (i = 0; i < n; i++) {
        delete array[i];
    }

    delete[]array;

    return EXIT_SUCCESS;
}

