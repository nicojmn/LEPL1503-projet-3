#ifndef MANAGEHEAP_H
#define MANAGEHEAP_H

#include <stdio.h>
#include <stdbool.h>
#include "kMeans.h"


/**
 * Structure regrouping all the arguments of the program
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

/**
 * Free all the data allocated in a k_means_t structure
 * @param KMeans : the structure we want to clean
 */
void clean(k_means_t *KMeans);

/**
 * Free the data of the global structures of the program
 * @param generalData : the instance's characteristics
 * @param startingCentroids : set of points used for kMeans calculation
 * @param iterationNumber : number of times we calculate new centroids
 * @param args : the arguments of the program
 */
void fullClean(data_t *generalData, point_t **startingCentroids, uint64_t iterationNumber, args_t args);

#endif
