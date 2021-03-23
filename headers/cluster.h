
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
#endif //CLUSTER_H
