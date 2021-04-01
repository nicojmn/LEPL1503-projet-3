#include "../headers/kMeans.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void updateCentroids(k_means_t *kMeans) {

    // Initialisation of all centroid coordinates to 0
    for (int i = 0; i < kMeans->k; ++i) {
        for (int j = 0; j < kMeans->dimension; ++j) {
            ((kMeans->centroids)[i].vector)[j] = (int64_t) 0;
        }
    }

    int64_t *clustersSize = (int64_t*) malloc((kMeans->k) * sizeof(int64_t));
    if (clustersSize == NULL) return;
    for (int i = 0; i < kMeans->k; ++i) {
        clustersSize[i] = (int64_t) 0;
    }

    // Sum
    for (int i = 0; i < kMeans->size; ++i) {
        int centroidID = (kMeans->points)[i].nearestCentroidID;
        for (int j = 0; j < kMeans->dimension; ++j) {
            ((kMeans->centroids)[centroidID].vector)[j] += ((kMeans->points)[i].vector)[j];
        }
        clustersSize[centroidID]++;
    }

    // Average
    for (int i = 0; i < kMeans->k; ++i) {
        for (int j = 0; j < kMeans->dimension; ++j) {
            /** Comments from the python script:
            /!\ we here use int(a/b) instead of a//b because // implements the floor division and with negative
             # numbers this is not an integer division as it rounds the result down
            */
            ((kMeans->centroids)[i].vector)[j] = (int64_t) (((kMeans->centroids)[i].vector)[j]
                                                            /clustersSize[i]);
        }
    }
    free(clustersSize);
}

int32_t assignVectorsToCentroids(k_means_t *kMeans,
                                 squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2,
                                                                          int32_t dimension)) {

    int32_t hasChanged = 0;

    for (int i = 0; i < kMeans->size; ++i) {
        // Let's find the closest centroid
        for (int j = 0; j < kMeans->k; ++j) {

            // If it's the first time this function is used
            int64_t oldDistance = INT64_MAX;
            if (((kMeans->points)[i]).nearestCentroidID != -1) {
                oldDistance = (int64_t) distanceFunction(&(kMeans->points)[i],
                                                         &(kMeans->centroids)[((kMeans->points)[i]).nearestCentroidID],
                                                         kMeans->dimension);
            }
            int64_t newDistance = (int64_t) distanceFunction(&(kMeans->points)[i], &(kMeans->centroids)[j],
                                                             kMeans->dimension);
            if (oldDistance > newDistance){
                hasChanged = 1;
                (kMeans->points)[i].nearestCentroidID = (int32_t) j;
            }
        }
    }
    return hasChanged;
}
void k_means(k_means_t *kMeans,
             squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2,
                                                      int32_t dimension)){

    //TODO : make distanceFunction as a global function ( if possible :D)

    int32_t hasChanged = 1;
    while (hasChanged == 1){
        hasChanged = assignVectorsToCentroids(kMeans,distanceFunction);
        updateCentroids(kMeans);
    }
}

