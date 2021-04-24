#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "../headers/kMeans.h"

void updateCentroids(kMeans_t *kMeans) {

    // Initialisation of all centroid coordinates to 0
    for (int32_t i = 0; i < kMeans->k; ++i) {
        for (int32_t j = 0; j < kMeans->dimension; ++j) {
            ((kMeans->centroids)[i].vector)[j] = (int64_t) 0;
        }
    }
    for (int32_t i = 0; i < kMeans->k; ++i) {
        (kMeans->clustersSize)[i] = (int64_t) 0;
    }
    // Sum
    for (uint64_t i = 0; i < kMeans->size; ++i) {
        int32_t centroidID = (kMeans->points)[i].nearestCentroidID;
        for (int32_t j = 0; j < kMeans->dimension; ++j) {
            ((kMeans->centroids)[centroidID].vector)[j] += ((kMeans->points)[i].vector)[j];
        }
        (kMeans->clustersSize)[centroidID]++;
    }
    // Average
    for (int32_t i = 0; i < kMeans->k; ++i) {
        for (int32_t j = 0; j < kMeans->dimension; ++j) {
            /** Comments from the python script:
            /!\ we here use int(a/b) instead of a//b because // implements the floor division and with negative
             # numbers this is not an integer division as it rounds the result down
            */
            ((kMeans->centroids)[i].vector)[j] = (int64_t) (((kMeans->centroids)[i].vector)[j]
                                                            / (kMeans->clustersSize)[i]);
        }
    }
}

int32_t assignVectorsToCentroids(kMeans_t *kMeans,
                                 squared_distance_func_t distanceFunction(const point_t *, const point_t *,
                                                                          uint32_t)) {
    int32_t hasChanged = 0;
    for (uint64_t i = 0; i < kMeans->size; ++i) {
        // Let's find the closest centroid
        int64_t currentDistance = INT64_MAX;
        int32_t currentCentroid;
        uint32_t oldCentroid = (kMeans->points)[i].nearestCentroidID;
        for (int32_t j = 0; j < kMeans->k; ++j) {
            int64_t newDistance = (int64_t) distanceFunction(&(kMeans->points)[i], &(kMeans->centroids)[j],
                                                             kMeans->dimension);
            if (newDistance < currentDistance) {
                currentDistance = newDistance;
                currentCentroid = (int32_t) j;
            }
        }
        (kMeans->points)[i].nearestCentroidID = currentCentroid;
        if (currentCentroid != oldCentroid) {
            hasChanged = 1;
        }
    }
    return hasChanged;
}

void runKMeans(kMeans_t *kMeans,
               squared_distance_func_t distanceFunction(const point_t *, const point_t *,
                                                        uint32_t)) {

    //TODO : make distanceFunction as a global function ( if possible :D)
    int32_t hasChanged = 1;
    while (hasChanged == 1) {
        hasChanged = assignVectorsToCentroids(kMeans, distanceFunction);
        updateCentroids(kMeans);

    }
}

kMeans_t *createOneInstance(int64_t **vectors, point_t **startingCentroidsID, uint32_t index, uint32_t k,
                            uint64_t size, uint32_t dimension) {
    kMeans_t *kMeans = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (kMeans == NULL) return NULL;
    kMeans->clustersSize = (int64_t *) malloc(k * sizeof(int64_t));
    if (kMeans->clustersSize == NULL) return NULL;
    kMeans->points = (point_t *) malloc(size * sizeof(point_t));
    if (kMeans->points == NULL) return NULL;
    kMeans->centroids = (point_t *) malloc(k * sizeof(point_t));
    if (kMeans->centroids == NULL) return NULL;

    kMeans->k = k;
    kMeans->size = size;
    kMeans->dimension = dimension;
    // setup centroids
    for (int32_t i = 0; i < k; ++i) {
        (kMeans->centroids)[i].vector = (int64_t *) malloc(dimension * sizeof(int64_t));
        if ((kMeans->centroids)[i].vector == NULL) return NULL;
        for (int32_t j = 0; j < dimension; ++j) {
            (kMeans->centroids)[i].vector[j] = (startingCentroidsID[index][i].vector)[j];
        }
    }
    // setup points
    for (uint64_t i = 0; i < size; ++i) {
        (kMeans->points)[i].vector = vectors[i];
    }
    return kMeans;
}


