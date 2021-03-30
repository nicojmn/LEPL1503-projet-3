
#ifndef CLUSTER_H
#define CLUSTER_H

#include "point.h"

#include <stdint.h>

typedef struct {
    point_t *firstPoint;
    point_t *lastPoint;
    point_t *centroid;
    int64_t size;
} cluster_t;


/**
 *
 * @param cluster : a pointer to the cluster to reset
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


/**
 *
 * @param clusters : array of clusters
 * @param clustersSize : size of clusters
 * @param distanceFunction : generic function to determine if we want manhattan or euclidean distance
 * @param distanceMode : a string which contains "manhattan" or "euclidean"
 *
 * @return true if the assignation has changed from the last iteration
 */
int32_t assignVectorsToCentroids(cluster_t *clusters, int64_t clustersSize,
                                 int64_t *distanceFunction(const point_t *, const point_t *, int32_t),
                                 char *distanceMode);

#endif //CLUSTER_H
