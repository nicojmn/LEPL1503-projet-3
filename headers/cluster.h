
#ifndef CLUSTER_H
#define CLUSTER_H

#include "point.h"
typedef struct {
    point_t *points;
    point_t *centroid;
    int64_t size;
} cluster_t;


/**
 *
 * @param cluster : a pointer to the cluster to reset
 *
 * @return : nothing
 *
 */
void emptyCluster(cluster_t *cluster);

/** Be careful this has not been tested yet */
// TODO : write docstring
/**
 *
 * @param clusters
 * @param clusterNumber
 * @param dimension
 */
void updateCentroids(cluster_t *clusters, uint32_t clustersNumber, int32_t dimension);

#endif //CLUSTER_H
