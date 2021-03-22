#include "../headers/cluster.h"

#include <stdlib.h>

void emptyCluster(cluster_t *cluster) {
    cluster->points = {}; // reset the array of points
    cluster->centroid = NULL;
}