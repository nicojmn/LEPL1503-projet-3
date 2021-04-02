#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include "headers/distance.h"
#include "headers/generateStartingCentroids.h"
#include "headers/kMeans.h"
#include "headers/createOutputFile.h"

int64_t **vectors;
int32_t dimension;
int64_t size;

typedef struct {
    FILE *input_stream;
    FILE *output_stream;
    uint32_t n_threads;
    uint32_t k;
    uint32_t n_first_initialization_points;
    bool quiet;
    squared_distance_func_t squared_distance_func;
} args_t;


void usage(char *prog_name) {
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "    %s [-p n_combinations_points] [-n n_threads] [input_filename]\n", prog_name);
    fprintf(stderr, "    -k n_clusters (default value: 2): the number of clusters to compute\n");
    fprintf(stderr, "    -p n_combinations (default value: equal to k): consider the n_combinations first points present in the input to generate possible initializations for the k-means algorithm\n");
    fprintf(stderr, "    -n n_threads (default value: 4): sets the number of computing threads that will be used to execute the k-means algorithm\n");
    fprintf(stderr, "    -f output_file (default value: stdout): sets the filename on which to write the csv result\n");
    fprintf(stderr, "    -q quiet mode: does not output the clusters content (the \"clusters\" column is simply not present in the csv)\n");
    fprintf(stderr, "    -d distance (manhattan by default): can be either \"euclidean\" or \"manhattan\". Chooses the distance formula to use by the algorithm to compute the distance between the points\n");
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

int main(int argc, char *argv[]) {
    args_t programArguments;   // allocate the args on the stack
    parse_args(&programArguments, argc, argv);

    if (programArguments.n_first_initialization_points < programArguments.k) {
        fprintf(stderr, "Cannot generate an instance of k-means with less initialization points than needed clusters: %"PRIu32" < %"PRIu32"\n",
                programArguments.n_first_initialization_points, programArguments.k);
        return -1;
    }
    // the following fprintf (and every code already present in this skeleton) can be removed, it is just an example to show you how to use the program arguments
    fprintf(stderr, "\tnumber of threads executing the LLoyd's algoprithm in parallel: %" PRIu32 "\n",
            programArguments.n_threads);
    fprintf(stderr, "\tnumber of clusters (k): %" PRIu32 "\n", programArguments.k);
    fprintf(stderr,
            "\twe consider all the combinations of the %" PRIu32 " first points of the input as initializations of the Lloyd's algorithm\n",
            programArguments.n_first_initialization_points);
    fprintf(stderr, "\tquiet mode: %s\n", programArguments.quiet ? "enabled" : "disabled");
    fprintf(stderr, "\tsquared distance function: %s\n",
            programArguments.squared_distance_func == squared_manhattan_distance ? "manhattan" : "euclidean");

    // TODO: parse the binary input file, compute the k-means solutions and write the output in a csv

    // TODO: Loading data: Gilles

    squared_distance_func_t generic_func = programArguments.squared_distance_func;

    int32_t k = programArguments.k;
    int32_t n = programArguments.n_first_initialization_points;
    int32_t iterationNumber = (int32_t) factorial(n) / (factorial(k) * factorial(n - k));

    point_t **startingCentroids = (point_t **) malloc(iterationNumber * sizeof(point_t *));
    for (int i = 0; i < iterationNumber; ++i) {
        startingCentroids[i] = (point_t *) malloc(k * sizeof(point_t));
    }
    generateSetOfStartingCentroids(startingCentroids, vectors, k, n, iterationNumber);

    csvFileHeadline(programArguments.quiet, programArguments.output_stream);

    for (int i = 0; i < iterationNumber; ++i) {
        k_means_t *kMeansSimulation = produce(vectors, startingCentroids, i, k, size, dimension);

        k_means(kMeansSimulation,
                (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);

        writeOneKmeans(kMeansSimulation, programArguments.quiet, programArguments.output_stream, startingCentroids[i], iterationNumber);
    }

    // TODO: Be careful everything must be freed
    for (int i = 0; i < iterationNumber; ++i) {
        free(startingCentroids[i]);
    }
    free(startingCentroids);

    // close the files opened by parse_args
    if (programArguments.input_stream != stdin) {
        fclose(programArguments.input_stream);
    }
    if (programArguments.output_stream != stdout) {
        fclose(programArguments.output_stream);
    }
    return 0;
}
