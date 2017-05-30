#include <iostream>
#include <defines.h>
#include <parser.h>
#include <moduleExecutor.h>

int main(int argc, char *argv[]) {
    //TODO @agus parsear --D1=<size>,<associativity>,<line size> y fijarse que sean números válidos.
    string simulatedCacheInfo = "";


    string moduleName = "blockSize";
    parser_output blockSizeOutput;
    string params = "";
    executeModule(moduleName, simulatedCacheInfo, params);
    parseDataMissRate(&blockSizeOutput, moduleName);

    unsigned long blockSize = blockSizeOutput.dw / blockSizeOutput.d1mw;
    cout << "Tamaño de Bloque: " << blockSize << " Bytes" << endl;


    moduleName = "cacheSize";
    string blockSizeParams;
    unsigned int n = 64;
    parser_output cacheSizeOutput;
    cacheSizeOutput.d1mw = 0;

    while (cacheSizeOutput.d1mw <= n) {
        n *= 2;
        blockSizeParams.append(to_string(blockSize)).append(" ").append(to_string(n));
        executeModule(moduleName, simulatedCacheInfo, blockSizeParams);
        parseDataMissRate(&cacheSizeOutput, moduleName);
        blockSizeParams.clear();
    }

    cout << "Tamaño Total: " << n / 2 * blockSize << " Bytes" << endl;

}


