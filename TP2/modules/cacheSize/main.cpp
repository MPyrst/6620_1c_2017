#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

void cacheSize(register unsigned int blockSize, register unsigned int n, char *array) {

    register unsigned long pos;
    register unsigned long i;
    for (i = 0; i < 100; i++) {
        for (pos = 0; pos < n; pos++) {
            char aux = array[blockSize * pos];
        }
    }

}


int main(int argc, char *argv[]) {
    unsigned int blockSize = (unsigned int) std::stoul(argv[1]);
    unsigned int n = (unsigned int) std::stoul(argv[2]);
    char array[blockSize * n];
    cacheSize(blockSize, n, array);
    return EXIT_SUCCESS;
}

