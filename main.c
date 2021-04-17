#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <pthread.h>
#include "headers/distance.h"
#include "headers/generateStartingCentroids.h"
#include "headers/kMeans.h"
#include "headers/createOutputFile.h"
#include "headers/readBinaryFile.h"
#include "headers/manageHeap.h"
#include "src/manageHeap.c"
#include "src/distance.c"
#include "src/generateStartingCentroids.c"
#include "src/kMeans.c"
#include "src/createOutputFile.c"
#include "src/readBinaryFile.c"

args_t programArguments;

data_t *generalData;
squared_distance_func_t generic_func;

point_t **startingCentroids;
uint32_t k;
uint64_t iterationNumber;

void usage(char *prog_name) {
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "    %s [-p n_combinations_points] [-n n_threads] [input_filename]\n", prog_name);
    fprintf(stderr, "    -k n_clusters (default value: 2): the number of clusters to compute\n");
    fprintf(stderr,
            "    -p n_combinations (default value: equal to k): consider the n_combinations first points present in the input to generate possible initializations for the k-means algorithm\n");
    fprintf(stderr,
            "    -n n_threads (default value: 4): sets the number of computing threads that will be used to execute the k-means algorithm\n");
    fprintf(stderr, "    -f output_file (default value: stdout): sets the filename on which to write the csv result\n");
    fprintf(stderr,
            "    -q quiet mode: does not output the clusters content (the \"clusters\" column is simply not present in the csv)\n");
    fprintf(stderr,
            "    -d distance (manhattan by default): can be either \"euclidean\" or \"manhattan\". Chooses the distance formula to use by the algorithm to compute the distance between the points\n");
}

int parse_args(args_t *args, int argc, char *argv[]) {
    memset(args, 0, sizeof(args_t));    // set everything to 0 by default
    // the default values are the following, they will be changed depending on the arguments given to the program
    args->k = 2;
    args->n_first_initialization_points = args->k;
    args->n_threads = 4;
    args->output_stream = stdout;
    args->quiet = false;
    args->squared_distance_func = squared_manhattan_distance;
    int opt;
    while ((opt = getopt(argc, argv, "n:p:k:f:d:q")) != -1) {
        switch (opt)
        {
            case 'n':
                args->n_threads = atoi(optarg);
                if (args->n_threads <= 0) {
                    fprintf(stderr, "Wrong number of threads. Needs a positive integer, received \"%s\"\n", optarg);
                    return -1;
                }
                break;
            case 'p':
                args->n_first_initialization_points = atoi(optarg);
                if (args->n_first_initialization_points <= 0) {
                    fprintf(stderr, "Wrong number of initialization points. Needs a positive integer, received \"%s\"\n", optarg);
                    return -1;
                }
                break;
            case 'k':
                args->k = atoi(optarg);
                if (args->k <= 0) {
                    fprintf(stderr, "Wrong k. Needs a positive integer, received \"%s\"\n", optarg);
                    return -1;
                }
                break;
            case 'f':
                args->output_stream = fopen(optarg, "w");
                if (!args->output_stream) {
                    fprintf(stderr, "could not open output file %s: %s\n", optarg, strerror(errno));
                    return -1;
                }
                break;
            case 'q':
                args->quiet = true;
                break;
            case 'd':
                if (strcmp("euclidean", optarg) == 0) {
                    args->squared_distance_func = squared_euclidean_distance;
                }
                break;
            case '?':
                usage(argv[0]);
                return 1;
            default:
                usage(argv[0]);
        }
    }

    if (optind == argc) {
        args->input_stream = stdin;
    } else {
        args->input_stream = fopen(argv[optind], "r");
        if (!args->input_stream) {
            fprintf(stderr, "could not open file %s: %s\n", argv[optind], strerror(errno));
            return -1;
        }
    }

    return 0;
}

void *runOneInstance(void *startEnd) {
    for (uint32_t i = ((uint32_t *) startEnd)[0]; i < ((uint32_t *) startEnd)[1]; ++i) {
        k_means_t *kMeansSimulation = produce(generalData->vectors, startingCentroids, i, k,
                                              generalData->size, generalData->dimension);
        k_means(kMeansSimulation,
                (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);
        //TODO : add the mutex or semaphore
        if (writeOneKMeans(kMeansSimulation, programArguments.quiet, programArguments.output_stream,
                           startingCentroids[i],
                           (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func) ==
            -1) {
            clean(kMeansSimulation);
            fullClean(generalData, startingCentroids, iterationNumber, programArguments);
            return (void *) -1;
        }
        clean(kMeansSimulation);
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    parse_args(&programArguments, argc, argv);

    if (programArguments.n_first_initialization_points < programArguments.k) {
        fprintf(stderr,
                "Cannot generate an instance of k-means with less initialization points than needed clusters: %"PRIu32" < %"PRIu32"\n",
                programArguments.n_first_initialization_points, programArguments.k);
        return -1;
    }
    // the following fprintf (and every code already present in this skeleton) can be removed, it is just an example to show you how to use the program arguments
    fprintf(stderr, "\tnumber of threads executing the LLoyd's algorithm in parallel: %" PRIu32 "\n",
            programArguments.n_threads);
    fprintf(stderr, "\tnumber of clusters (k): %" PRIu32 "\n", programArguments.k);
    fprintf(stderr,
            "\twe consider all the combinations of the %" PRIu32 " first points of the input as initializations of the Lloyd's algorithm\n",
            programArguments.n_first_initialization_points);
    fprintf(stderr, "\tquiet mode: %s\n", programArguments.quiet ? "enabled" : "disabled");
    fprintf(stderr, "\tsquared distance function: %s\n",
            programArguments.squared_distance_func == squared_manhattan_distance ? "manhattan" : "euclidean");


    generalData = (data_t *) malloc(sizeof(data_t));
    if (generalData == NULL) return -1;
    loadData(programArguments.input_stream, generalData);
    generic_func = programArguments.squared_distance_func;

    k = programArguments.k;
    uint32_t n = programArguments.n_first_initialization_points;
    iterationNumber = combinatorial(n, k);
    startingCentroids = (point_t **) malloc(iterationNumber * sizeof(point_t *));
    for (uint64_t i = 0; i < iterationNumber; ++i) {
        startingCentroids[i] = (point_t *) malloc(k * sizeof(point_t));
    }
    generateSetOfStartingCentroids(startingCentroids, generalData->vectors, k, n, iterationNumber);
    csvFileHeadline(programArguments.quiet, programArguments.output_stream);

    pthread_t threads[programArguments.n_threads];
    uint32_t nbrOfLinesPerThread = (uint32_t) iterationNumber / programArguments.n_threads;
    uint16_t rest = (uint16_t) iterationNumber % programArguments.n_threads;
    uint32_t listOfIndexes[2];
    uint32_t start = 0;
    uint32_t end = nbrOfLinesPerThread;
    for (int i = 0; i < programArguments.n_threads; i++) {
        if (rest > 0) {
            end++;
            rest--;
        }
        listOfIndexes[0] = start;
        listOfIndexes[1] = end;
        start = end;
        end += nbrOfLinesPerThread;
        if (pthread_create(&threads[i], NULL, runOneInstance, listOfIndexes) != 0) return -1;
    }

    for (int i = 0; i < programArguments.n_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    fullClean(generalData, startingCentroids, iterationNumber, programArguments);
    printf("The job is done !\n");
    return 0;
}
