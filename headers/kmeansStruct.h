#ifndef K_MEANS_STRUCT
#define K_MEANS_STRUCT

#include <stdint.h>


/**
 * Structure representing a graphical point with it's coords as vector
 * and the nearest centroid
 *
 * /!\ We don't use any cluster structure but instead we linked each point to
 * its closest centroid (using nearestCentroidID)
 */
typedef struct {
    int64_t *vector;
    uint32_t nearestCentroidID;
} point_t;

/**
 * Structure containing all the necessary features for one iteration of Lloyd's algorithm
 */
typedef struct {
    point_t *centroids;
    uint64_t *clustersSize;
    uint32_t k;
    point_t *points;
    uint32_t dimension;
    uint64_t size;
} kMeans_t;

/**
 * Structure containing the instance's features and all the points from the input file
 * We don't copy the points' coordinate anywhere else but only use pointers
 */
typedef struct {
    int64_t **vectors;
    uint32_t dimension;
    uint64_t size;
} data_t;

#endif
