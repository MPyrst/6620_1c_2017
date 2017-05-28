#include "moduleExecutor.h"

void executeModule(string moduleName, string simulatedCacheInfo) {
    string logFile = moduleName + ".log";
    string outputFile = moduleName + ".out";
    string readableOutput = moduleName + ".readable";

    //valgrind --tool=cachegrind --log-file=$(logFile) --cachegrind-out-file --D1=<size>,<associativity>,<line size> ./modules/$(moduleName)/$(moduleName)
    string cacheGrindCall("valgrind --tool=cachegrind --log-file=");
    cacheGrindCall.append(logFile);
    cacheGrindCall.append(" --cachegrind-out-file=").append(outputFile);
    if (!simulatedCacheInfo.empty()) {
        cacheGrindCall.append(simulatedCacheInfo);
    }
    cacheGrindCall.append(" ./modules/").append(moduleName).append("/").append(moduleName);
    system(cacheGrindCall.c_str());

    //cg_annotate --auto=yes --show=Dr,Dw,D1mr,D1mw $(outputFile)
    string cg_annotateCall("cg_annotate --auto=yes --show=Dr,Dw,D1mr,D1mw ");
    cg_annotateCall.append(outputFile).append(">").append(readableOutput);
    system(cg_annotateCall.c_str());
}