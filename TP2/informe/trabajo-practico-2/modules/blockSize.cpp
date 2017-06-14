#include <iostream>
#include <math.h>

static const int ITERATION_SIZE = (int) pow(2, 20);
using namespace std;

void blockSize(char *array) {
    register unsigned long pos;
    char aux;
    for (pos = 0; pos < ITERATION_SIZE; pos++) {
        aux = array[pos];
    }
}


int main(int argc, char *argv[]) {
    char array[ITERATION_SIZE];
    blockSize(array);
    return EXIT_SUCCESS;
}

