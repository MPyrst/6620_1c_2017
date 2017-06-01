#include <iostream>
#include <defines.h>
#include <parser.h>
#include <getopt.h>
#include <moduleExecutor.h>

bool validateCacheInfo(string data);

int main(int argc, char *argv[]) {
    //TODO @agus parsear --D1=<size>,<associativity>,<line size> y fijarse que sean números válidos.
    int parameter;
    string cache = "";

    static struct option long_options[] =
    {
    /* These options don’t set a flag.
     We distinguish them by their indices. */
    {"version", no_argument,       0, 'v'},
    {"help",    no_argument,       0, 'h'},
    {"D1=",  required_argument, 0, 'l'},
    {0, 0,                         0, 0}
    };

    opterr = 0;
    int option_index = 0;

    while ((parameter = getopt_long_only(argc, argv, "vhl:",
                                    long_options, &option_index)) != -1)
        switch (parameter) {
            case 'v':
                printf("This is version 1.0 from tp3: Memorias caches.\n");
                exit(EXIT_FAILURE);
            case 'h':
                printf("Usage:\n"
                       " tp0 -h\n"
                       " tp0 -v\n"
                       " tp0 -D1=size, ways, bytes per line\n"
                       );
                exit(EXIT_FAILURE);
            case 'l':
                cache = optarg;
                break;
            case '?':
                if (optopt == 'l') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if (isprint (optopt)) {
                    fprintf(stderr, "Unknown argument '-%c'.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);

                }
                exit(EXIT_FAILURE);
            default:
                exit(EXIT_FAILURE);
        }

    /* cache value */
    int size, ways, bytesPerLine;
    bool validInfo;
    if (cache.size() > 0) {
        string aux = "";
	int pos = cache.find(',');
	if (pos != -1) {
	    aux = cache.substr(0, pos);
	    validInfo = validateCacheInfo(aux);
	    if (!validInfo) {
		fprintf(stderr, "The size info is not valid.\n");
		exit(EXIT_FAILURE);
	    }
	    size = stoi(aux);
	    aux.clear();
	    cache = cache.substr(pos + 1);
	    pos = cache.find(',');
            if (pos != -1) {
	    	aux = cache.substr(0, pos);
	    	validInfo = validateCacheInfo(aux);
	    	if (!validInfo) {
			fprintf(stderr, "The ways info is not valid.\n");
			exit(EXIT_FAILURE);
	    	}
	    	ways = stoi(aux);;
	    	aux.clear();
           	aux = cache.substr(pos + 1);
	    	validInfo = validateCacheInfo(aux);
	    	if (!validInfo) {
			fprintf(stderr, "The bytes per line info is not valid.\n");
			exit(EXIT_FAILURE);
	    	}
	    	bytesPerLine = stoi(aux);  
	    }	
        } else {
	   fprintf(stderr, "The info of the cache is not valid.\n");
	   exit(EXIT_FAILURE);
        }
    }


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

bool validateCacheInfo(string data) {
    int aux = stoi(data);
    if (aux == 1 || (aux % 2 == 0)) {
       return true;
    }
    return false;
}


