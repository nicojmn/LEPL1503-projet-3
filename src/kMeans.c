#include "../headers/kMeans.h"
#include "../headers/distance.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

// TODO : write test for function
int32_t assignVectorsToCentroids(cluster_t *clusters, int64_t clustersSize,
                                 int64_t *distanceFunction(const point_t *, const point_t *, int32_t),
                                 char *distanceMode) {
    // Initialise variable
    cluster_t *newClusters = (cluster_t *) malloc(sizeof(cluster_t) * clustersSize);
    if (newClusters == NULL) return 0;
    int32_t unchanged = 0;

    // Select distance
    if (strcasecmp(distanceMode, "manhattan") == 0) {
        distanceFunction = (int64_t *(*)(const point_t *, const point_t *, int32_t)) squared_manhattan_distance;
    } else if (strcasecmp(distanceMode, "euclidean") == 0) {
        distanceFunction = (int64_t *(*)(const point_t *, const point_t *, int32_t)) squared_euclidean_distance;
    } else {
        //TODO : raise error
    }

    for (int cluster = 0; cluster < clustersSize; ++cluster) {
        cluster_t *current = &clusters[cluster];

        // Find closest centroid for vector
        for (int vector = 0; vector < current->size; ++vector) {
            int64_t closestCentroidID = -1;
            int64_t closest_centroid_distance = INT64_MAX;
            for (int centroidID = 0; centroidID < clustersSize; ++centroidID) {
                int64_t distance = (int64_t) distanceFunction(current->centroid, clusters[centroidID].centroid,
                                                              current->centroid->dimension);

                if (distance < closest_centroid_distance) {
                    closestCentroidID = centroidID;
                    closest_centroid_distance = distance;
                }
            }
            // Add vector in the new array and observe if the current vector changes its cluster
            newClusters[closestCentroidID].centroid->vector = current->centroid->vector;
            unchanged = unchanged && clusters[closestCentroidID].centroid == current->centroid;
        }
    }
    return !unchanged;
}