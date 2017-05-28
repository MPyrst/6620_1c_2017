#include <iostream>
#include <defines.h>
#include <parser.h>
#include <moduleExecutor.h>

int main(int argc, char *argv[]) {
    //TODO parse --D1=<size>,<associativity>,<line size>
    string simulatedCacheInfo = "";


    string moduleName = "blockSize";
    parser_output blockSizeOutput;
    executeModule(moduleName, simulatedCacheInfo);
    parseDataMissRate(&blockSizeOutput, moduleName);

    unsigned long blockSize = blockSizeOutput.dw / blockSizeOutput.d1mw;
    std::cout << "Tamaño de bloque: " << blockSize << " Bytes" << std::endl;
}


