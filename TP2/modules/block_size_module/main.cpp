#include <iostream>

#define ITERATION_SIZE 1024*1024

void blockSize(char *array) {
    for (unsigned long pos = 0; pos < ITERATION_SIZE; pos++) {
        array[pos] = 'a';
    }
}


int main(int argc, char *argv[]) {
    char array[1024 * 1024];
    blockSize(array);
    return 0;
}

