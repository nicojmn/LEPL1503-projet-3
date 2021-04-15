
#ifndef POINT_H
#define POINT_H

#include <stdint.h>

typedef struct {
    int64_t *vector;
    int32_t nearestCentroidID;
} point_t;
typedef struct {
    point_t *centroids;
    int64_t *clustersSize;
    uint32_t k;
    point_t *points;
    uint32_t dimension;
    uint64_t size;

} k_means_t;


typedef struct {
    int64_t **vectors;
    uint32_t dimension;
    uint64_t size;
} data_t;

#endif
