#ifndef MANAGEHEAP_H
#define MANAGEHEAP_H

#include <stdio.h>
#include <stdbool.h>
#include "kMeans.h"

// #TODO Décrire la structure

typedef struct {
    FILE *input_stream;
    FILE *output_stream;
    uint32_t n_threads;
    uint32_t k;
    uint32_t n_first_initialization_points;
    bool quiet;
    squared_distance_func_t squared_distance_func;
} args_t;

void clean(k_means_t *KMeans);

void fullClean(data_t *generalData, point_t **startingCentroids, uint64_t iterationNumber, args_t args);

#endif
