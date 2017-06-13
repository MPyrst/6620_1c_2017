#include "parser.h"

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

    ifstream t(outputFile);
    stringstream buffer;
    buffer << t.rdbuf();

    if (!t.good()) {
        fprintf(stderr, "Error creating file %s.\n", outputFile.c_str());
        t.close();
        return false;
    }

    //Example: 4,194,307 1,048,580     1 16,385  .../TP2/modules/blockSize/main.cpp:blockSize(char*)
    string info = buffer.str();

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


   /* if (remove(inputFile.c_str()) != 0) {
        fprintf(stderr, "Error removing file %s.\n", inputFile.c_str());
    }

    if (remove(outputFile.c_str()) != 0) {
        fprintf(stderr, "Error removing file %s.\n", outputFile.c_str());
    }*/

    /* cout << "dr:" << parserOutput->dr << endl;
       cout << "dw:" << parserOutput->dw << endl;
       cout << "d1mr:" << parserOutput->d1mr << endl;
       cout << "d1mw:" << parserOutput->d1mw << endl;*/

    t.close();
    return true;
}
