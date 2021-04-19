#ifndef K_MEANS_STRUCT
#define K_MEANS_STRUCT

#include <stdint.h>

// #TODO On ferait bien une description de chaque structure pour expliquer à quoi elle sert

/**
 * Structure representing a graphical point with it's coords vector and the nearest centroid
 */
typedef struct {
    int64_t *vector;
    int32_t nearestCentroidID;
} point_t;

/**
 * Structure containing all the necessary data for one iteration of the kMeans algorithm
 */
typedef struct {
    point_t *centroids;
    int64_t *clustersSize;
    uint32_t k;
    point_t *points;
    uint32_t dimension;
    uint64_t size;
} k_means_t;

/**
 * Structure containing the instance's characteristics
 */
typedef struct {
    int64_t **vectors;
    uint32_t dimension;
    uint64_t size;
} data_t;

#endif
