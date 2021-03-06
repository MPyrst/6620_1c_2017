#include "moduleExecutor.h"

void executeModule(string &moduleName, string &simulatedCacheInfo, string &params) {
    string logFile = moduleName + ".log";
    string outputFile = moduleName + ".out";
    string readableOutput = moduleName + ".readable";

    //valgrind --tool=cachegrind --log-file=$(logFile) --cachegrind-out-file=$(outputFile) --D1=<size>,<associativity>,<line size> ./modules/$(moduleName)/$(moduleName)
    string cacheGrindCall("valgrind --tool=cachegrind --log-file=");
    cacheGrindCall.append(logFile);
    cacheGrindCall.append(" --cachegrind-out-file=").append(outputFile);
    if (!simulatedCacheInfo.empty()) {
        //cout << "Params: " << simulatedCacheInfo << endl;
        cacheGrindCall.append(" ").append(simulatedCacheInfo);
    }
    cacheGrindCall.append(" ./modules/").append(moduleName).append("/").append(moduleName);
    if (!params.empty()) {
        //cout << "Params: " << params << endl;
        cacheGrindCall.append(" ").append(params);
    }

    //cout << "Call: " << cacheGrindCall << endl;
    system(cacheGrindCall.c_str());

    ifstream t(outputFile);
    if (!t.good()) {
        fprintf(stderr, "Error executing module %s.\n", moduleName.c_str());
        t.close();
        exit(EXIT_FAILURE);
    }

    t.close();

    //cg_annotate --auto=yes --show=Dr,Dw,D1mr,D1mw $(outputFile)
    string cg_annotateCall("cg_annotate --auto=yes --threshold=0.000001 --show=Dr,Dw,D1mr,D1mw ");
    cg_annotateCall.append(outputFile).append(">").append(readableOutput);
    system(cg_annotateCall.c_str());

    if (remove(logFile.c_str()) != 0) {
        fprintf(stderr, "Error removing file %s.\n", logFile.c_str());
    }

    if (remove(outputFile.c_str()) != 0) {
        fprintf(stderr, "Error removing file %s.\n", outputFile.c_str());
    }
}