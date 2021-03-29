
#ifndef UPDATECENTROIDS_H
#define UPDATECENTROIDS_H
#include <stdint.h>

#include "cluster.h"

/**
 *
 */

void updateCentroids(cluster_t *clusters, uint32_t clustersNumber, int32_t dimension);


#endif //UPDATECENTROIDS_H
