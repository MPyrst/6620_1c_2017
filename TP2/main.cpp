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

    unsigned long cacheSize = n / 2 * blockSize;
    cout << "Tamaño Total: " << cacheSize << " Bytes" << endl;

    //TODO terminar
/*    moduleName = "cacheAssociativity";
    string cacheAssociativityParams;
    parser_output associativityOutput;
    n = 1;
    while (associativityOutput.d1mw == 0) {
        cacheAssociativityParams.append(to_string(blockSize)).append(" ")
        .append(to_string(cacheSize)).append(" ").append(to_string(n));
        executeModule(moduleName, simulatedCacheInfo, blockSizeParams);
        parseDataMissRate(&associativityOutput, moduleName);
        n = n * 2;
    }
    cout << "#Vias: " << n / 2 << endl;*/

    return EXIT_SUCCESS;
}


