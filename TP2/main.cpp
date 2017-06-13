#include <iostream>
#include <defines.h>
#include <parser.h>
#include <getopt.h>
#include <moduleExecutor.h>

bool validateCacheInfo(string data);

int main(int argc, char *argv[]) {
    int parameter;
    string values = "";
    string simulatedCacheInfo = "";

    static struct option long_options[] =
    {
    /* These options don’t set a flag.
     We distinguish them by their indices. */
    {"version", no_argument,       0, 'v'},
    {"help",    no_argument,       0, 'h'},
    {"D1=",     required_argument, 0, 'l'},
    {0, 0,                         0, 0}
    };

    opterr = 0;
    int option_index = 0;

    while ((parameter = getopt_long_only(argc, argv, "vhl:",
                                         long_options, &option_index)) != -1)
        switch (parameter) {
            case 'v':
                printf("This is version 1.0 from tp2: Memorias cache.\n");
                exit(EXIT_FAILURE);
            case 'h':
                printf("Usage:\n"
                       " tp2 -h\n"
                       " tp2 -v\n"
                       " tp2 -D1=size, ways, bytes per line\n"
                );
                exit(EXIT_FAILURE);
            case 'l':
                values = optarg;
                break;
            case '?':
                if (optopt == 'l') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Unknown argument '-%c'.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
                }
                exit(EXIT_FAILURE);
            default:
                exit(EXIT_FAILURE);
        }


    bool validInfo;
    string toCheckValues = values;

    if (toCheckValues.size() > 0) {
        string aux = "";
        size_t pos = toCheckValues.find(',');
        if (pos != std::string::npos) {
            aux = toCheckValues.substr(0, pos);
            validInfo = validateCacheInfo(aux);
            if (!validInfo) {
                fprintf(stderr, "The size info is not valid.\n");
                exit(EXIT_FAILURE);
            }
            aux.clear();
            toCheckValues = toCheckValues.substr(pos + 1);
            pos = toCheckValues.find(',');
            if (pos != std::string::npos) {
                aux = toCheckValues.substr(0, pos);
                validInfo = validateCacheInfo(aux);
                if (!validInfo) {
                    fprintf(stderr, "The ways info is not valid.\n");
                    exit(EXIT_FAILURE);
                }
                aux.clear();
                aux = toCheckValues.substr(pos + 1);
                validInfo = validateCacheInfo(aux);
                if (!validInfo) {
                    fprintf(stderr, "The bytes per line info is not valid.\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "The info of the cache is not valid.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "The info of the cache is not valid.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (!values.empty()) {
        simulatedCacheInfo.append("--D1=").append(values);
    }

    string moduleName = "blockSize";
    parser_output blockSizeOutput;
    string params = "";
    executeModule(moduleName, simulatedCacheInfo, params);
    bool success = parseDataMissRate(&blockSizeOutput, moduleName);
    if (!success) {
        fprintf(stderr, "There was a problem parsing the %s input.\n", moduleName.c_str());
        exit(EXIT_FAILURE);
    }

    unsigned long blockSize = (blockSizeOutput.dr / 2) / blockSizeOutput.d1mr;
    cout << "Tamaño de Bloque: " << blockSize << " Bytes" << endl;

    moduleName = "cacheSize";
    params = "";
    unsigned int n = 128;
    parser_output cacheSizeOutput;
    cacheSizeOutput.d1mw = 0;

    while (cacheSizeOutput.d1mw <= n) {
        params.append(to_string(blockSize)).append(" ").append(to_string(n));
        executeModule(moduleName, simulatedCacheInfo, params);
        success = parseDataMissRate(&cacheSizeOutput, moduleName);
        if (!success) {
            fprintf(stderr, "There was a problem parsing the %s input.\n", moduleName.c_str());
            exit(EXIT_FAILURE);
        }
        params.clear();
        if (n >= cacheSizeOutput.d1mw) {
            n *= 2;
        }
    }

    unsigned long cacheSize = n * blockSize;
    cout << "Tamaño Total: " << cacheSize << " Bytes" << endl;


    moduleName = "cacheAssociativity";
    string cacheAssociativityParams;
    parser_output associativityOutput;
    associativityOutput.d1mw = 0;
    n = 1;
    while (associativityOutput.d1mw == 0) {
        cacheAssociativityParams.append(to_string(blockSize)).append(" ")
        .append(to_string(cacheSize)).append(" ").append(to_string(n));
        executeModule(moduleName, simulatedCacheInfo, cacheAssociativityParams);
        success = parseDataMissRate(&associativityOutput, moduleName);
        if (!success) {
            fprintf(stderr, "There was a problem parsing the %s input.\n", moduleName.c_str());
            exit(EXIT_FAILURE);
        }
        cacheAssociativityParams.clear();
        if (associativityOutput.d1mw == 0) {
            n = n * 2;
        }
    }

    cout << "#Vias: " << n / 2 << endl;
    return EXIT_SUCCESS;
}

bool validateCacheInfo(string data) {
    int aux = stoi(data);
    if (aux > 0) {
        if (aux == 1 || ((aux & (aux - 1)) == 0)) {
            return true;
        }
    }
    return false;
}


