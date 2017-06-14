#include <iostream>
#include <defines.h>
#include <parser.h>
#include <getopt.h>
#include <moduleExecutor.h>

bool validateCacheInfo(string &data);

void validateParams(string params);

unsigned long getBlockSize(string &simulatedCacheInfo);

unsigned long getCacheSize(unsigned long blockSize, string &simulatedCacheInfo);

int getWaysQuantity(unsigned long blockSize, unsigned long cacheSize, string &simulatedCacheInfo);

int main(int argc, char *argv[]) {
    int parameter;
    string values = "";
    string simulatedCacheInfo = "";

    /* These options do not set a flag. We distinguish them by their indices.*/
    static struct option long_options[] =
    {
    {"version", no_argument, 0,          'v'},
    {"help",    no_argument, 0,          'h'},
    {"D1=",     required_argument, NULL, 'l'},
    {0, 0,                   0,          0}
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

    if (values.size() > 0) {
        validateParams(values);
        simulatedCacheInfo.append("--D1=").append(values);
    }


    unsigned long blockSize = getBlockSize(simulatedCacheInfo);
    cout << "Tamanio de Bloque: " << blockSize << " Bytes" << endl;

    unsigned long cacheSize = getCacheSize(blockSize, simulatedCacheInfo);
    cout << "Tamanio Total: " << cacheSize << " Bytes" << endl;

    const int &waysQuantity = getWaysQuantity(blockSize, cacheSize, simulatedCacheInfo);

    cout << "#Vias: " << waysQuantity << endl;
    return EXIT_SUCCESS;
}


void validateParams(string toCheckValues) {
    bool validInfo;
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

bool validateCacheInfo(string &data) {
    int aux = stoi(data);
    if (aux > 0) {
        if (aux == 1 || ((aux & (aux - 1)) == 0)) {
            return true;
        }
    }
    return false;
}

unsigned long getBlockSize(string &simulatedCacheInfo) {
    string moduleName = "blockSize";
    parser_output blockSizeOutput;
    string params = "";
    executeModule(moduleName, simulatedCacheInfo, params);
    bool success = parseDataMissRate(&blockSizeOutput, moduleName);
    if (!success) {
        fprintf(stderr, "There was a problem parsing the %s input.\n", moduleName.c_str());
        exit(EXIT_FAILURE);
    }

    return (blockSizeOutput.dr / 2) / blockSizeOutput.d1mr;
}

unsigned long getCacheSize(unsigned long blockSize, string &simulatedCacheInfo) {
    string moduleName = "cacheSize";
    string params = "";
    unsigned int n = 32;
    parser_output cacheSizeOutput;
    cacheSizeOutput.d1mw = 0;

    while (cacheSizeOutput.d1mw <= n) {
        params.append(to_string(blockSize)).append(" ").append(to_string(n));
        executeModule(moduleName, simulatedCacheInfo, params);
        bool success = parseDataMissRate(&cacheSizeOutput, moduleName);
        if (!success) {
            fprintf(stderr, "There was a problem parsing the %s input.\n", moduleName.c_str());
            exit(EXIT_FAILURE);
        }
        params.clear();
        if (n >= cacheSizeOutput.d1mw) {
            n *= 2;
        }
    }

    return (n / 2) * blockSize;
}

int getWaysQuantity(unsigned long blockSize, unsigned long cacheSize, string &simulatedCacheInfo) {
    string moduleName = "cacheAssociativity";
    string cacheAssociativityParams;
    parser_output associativityOutput;
    associativityOutput.d1mw = 0;
    unsigned int n = 1;
    while (associativityOutput.d1mw == 0) {
        cacheAssociativityParams.append(to_string(blockSize)).append(" ")
        .append(to_string(cacheSize)).append(" ").append(to_string(n));
        executeModule(moduleName, simulatedCacheInfo, cacheAssociativityParams);
        bool success = parseDataMissRate(&associativityOutput, moduleName);
        if (!success) {
            fprintf(stderr, "There was a problem parsing the %s input.\n", moduleName.c_str());
            exit(EXIT_FAILURE);
        }
        //cout << "N: " << n << " d1mw: " << associativityOutput.d1mw << endl;
        cacheAssociativityParams.clear();
        if (associativityOutput.d1mw == 0) {
            n = n * 2;
        }
    }

    return std::max(1, (const int &) n / 2);
}