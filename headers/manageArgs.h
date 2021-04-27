#ifndef PROJET_CMAKE_MANAGEARGS_H
#define PROJET_CMAKE_MANAGEARGS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <errno.h>

#include "kMeans.h"


/**
 * Structure gathering all the arguments given in command line
 */
typedef struct {
    FILE *input_stream;
    FILE *output_stream;
    uint32_t n_threads;
    uint32_t k;
    uint32_t n_first_initialization_points;
    bool quiet;
    squared_distance_func_t squared_distance_func;
} args_t;

void usage(char *prog_name);

int parse_args(args_t *args, int argc, char *argv[]);

#endif //PROJET_CMAKE_MANAGEARGS_H