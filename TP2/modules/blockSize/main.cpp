#include <iostream>

static const int ITERATION_SIZE = 1024 * 1024;

void blockSize(char *array) {
    register unsigned long pos;
    for (pos = 0; pos < ITERATION_SIZE; pos++) {
        array[pos] = 'A';
    }
}


int main(int argc, char *argv[]) {
    char array[ITERATION_SIZE];
    blockSize(array);
    return EXIT_SUCCESS;
}

