#include "../headers/cluster.h"

#include <stdint.h>

/** Be careful this has not been tested yet */
void updateCentroids(cluster_t *clusters, uint32_t clusterNumber, int32_t dimension) {

    for (int i = 0; i < clusterNumber; ++i) {
        for (int j = 0; j < dimension; ++j) {
            clusters[i].centroid->vector[j] = (int64_t) 0;
            for (int k = 0; k < clusters[i].size; ++k) {
                clusters[i].centroid->vector[j] += clusters[i].points[k].vector[j];
            }
            /** Comments from the python scripts
            /!\ we here use int(a/b) instead of a//b because // implements the floor division and with negative
             # numbers this is not an integer division as it rounds the result down
            */
            clusters[i].centroid->vector[j] = (int64_t) (clusters[i].centroid->vector[j] / clusters[i].size);
        }
    }
}