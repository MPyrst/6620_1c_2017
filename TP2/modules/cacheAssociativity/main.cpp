#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;
//TODO terminar
/*void cacheAssociativity(register unsigned int blockSize, register unsigned int cacheSize, register unsigned int n,
                        char array[n][cacheSize]) {

    register unsigned int j = 0;
    register unsigned int i = 0;

    register unsigned int blocksQuantity = cacheSize / blockSize / n;

    for (j = 0; j < n; j++) {//associativity
        for (i = 0; i < blocksQuantity; i++) {//blocks along same way
            array[j][i * blockSize] = 'F';
        }
    }

    for (j = 0; j < n; j++) {
        array[j][0] = 'E';
    }
}


int main(int argc, char *argv[]) {
    unsigned int blockSize = (unsigned int) std::stoul(argv[1]);
    unsigned int cacheSize = (unsigned int) std::stoul(argv[2]);
    unsigned int n = (unsigned int) std::stoul(argv[3]);

    char array[n][cacheSize];

    cacheAssociativity(blockSize, cacheSize, n, array);
    return EXIT_SUCCESS;
}*/

