#include "parser.h"

/* CacheGrind with cg_annotate example
 * Example from https://accu.org/index.php/journals/1886
--------------------------------------------------------------------------------
I1 cache:         32768 B, 64 B, 8-way associative
D1 cache:         32768 B, 64 B, 8-way associative
LL cache:         8388608 B, 64 B, 16-way associative
Command:          ./tp2
Data file:        cachegrind.out.13312
Events recorded:  Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
Events shown:     Dr Dw D1mr D1mw
Event sort order: Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
Thresholds:       0.1 100 100 100 100 100 100 100 100
Include dirs:
User annotated:
Auto-annotation:  off

--------------------------------------------------------------------------------
         Dr        Dw   D1mr  D1mw
--------------------------------------------------------------------------------
347,549,352 8,191,748 13,563 2,178  PROGRAM TOTALS

--------------------------------------------------------------------------------
         Dr        Dw  D1mr  D1mw  file:function
--------------------------------------------------------------------------------
340,937,515 5,000,000     0     0  /home/federicofarina/Workspace/6620_1c_2017/TP2/main.cpp:isPrime(int)
3,000,000 2,000,000     0     0  /usr/include/c++/5/cmath:__gnu_cxx::__enable_if<std::__is_integer<int>::__value, double>::__type std::sqrt<int>(int)
3,078,503 1,000,003     0     0  /home/federicofarina/Workspace/6620_1c_2017/TP2/main.cpp:main
152,610    50,041 1,862    11  /build/glibc-GKVZIf/glibc-2.23/elf/dl-lookup.c:_dl_lookup_symbol_x*/

string do_replace(string const &in, string const &from, string const &to) {
    return std::regex_replace(in, std::regex(from), to);
}

bool parseDataMissRate(parser_output *parserOutput, string &moduleName) {
    //grep :$(moduleName) $(moduleName).readable > $(moduleName).grepOut
    string outputFile = moduleName + ".grepOut";
    string inputFile = moduleName + ".readable";

    string grepCall("grep ");
    grepCall.append("\":").append(moduleName).append("\" ");
    grepCall.append(inputFile);
    grepCall.append(" > ").append(outputFile);
    system(grepCall.c_str());

    //cout << "Grep: " << grepCall << endl;

    ifstream t(outputFile);
    stringstream buffer;
    buffer << t.rdbuf();

    if (!t.good()) {
        //TODO error handling
        return false;
    }

    //Example: 4,194,307 1,048,580     1 16,385  /home/federicofarina/Workspace/6620_1c_2017/TP2/modules/blockSize/main.cpp:blockSize(char*)
    string info = buffer.str();
    //cout << "Info:" << buffer.str() << endl;

    char line[info.size() + 1];
    std::copy(info.begin(), info.end(), line);
    line[info.size()] = '\0';

    vector<string> tokens;
    unsigned int pos = 0;
    char *token = strtok(line, " \r\n");
    while (token != NULL && pos < SHOW_INFO_QUANTITY) {
        tokens.push_back(token);
        token = strtok(NULL, " \r\n");
        pos++;
    }

    parserOutput->dr = stoul(do_replace(tokens[0], ",", ""));
    parserOutput->dw = stoul(do_replace(tokens[1], ",", ""));;
    parserOutput->d1mr = stoul(do_replace(tokens[2], ",", ""));;
    parserOutput->d1mw = stoul(do_replace(tokens[3], ",", ""));

    /* cout << "dr:" << parserOutput->dr << endl;
     cout << "dw:" << parserOutput->dw << endl;
     cout << "d1mr:" << parserOutput->d1mr << endl;
     cout << "d1mw:" << parserOutput->d1mw << endl;*/

    return true;
}
