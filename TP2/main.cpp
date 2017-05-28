#include <iostream>
#include <defines.h>
#include <parser.h>
#include <moduleExecutor.h>

int main(int argc, char *argv[]) {
    //TODO @agus parsear --D1=<size>,<associativity>,<line size> y fijarse que sean números válidos.
    string simulatedCacheInfo = "";


    string moduleName = "blockSize";
    parser_output blockSizeOutput;
    executeModule(moduleName, simulatedCacheInfo);
    parseDataMissRate(&blockSizeOutput, moduleName);

    unsigned long blockSize = blockSizeOutput.dw / blockSizeOutput.d1mw;
    std::cout << "Tamaño de bloque: " << blockSize << " Bytes" << std::endl;
}


