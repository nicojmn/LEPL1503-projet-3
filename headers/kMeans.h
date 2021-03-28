#ifndef K_MEANS
#define K_MEANS

#include "cluster.h"

typedef struct {
    cluster_t *clusters;
    point_t **points;
    uint32_t dimension;
    uint32_t size;
} k_means_t;

#endif //K_MEANS
