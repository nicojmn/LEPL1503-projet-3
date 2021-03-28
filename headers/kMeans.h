#ifndef K_MEANS
#define K_MEANS

#include "cluster.h"

typedef struct {
    cluster_t *clusters;
    point_t **points;
    int64_t dimension;
    int64_t size;
} k_means_t;

#endif //K_MEANS
