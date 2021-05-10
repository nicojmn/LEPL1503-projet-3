#include "../headers/kMeans.h"

void updateCentroids(kMeans_t *kMeans) {

    // Initialisation of all centroid coordinates to 0
    for (uint32_t i = 0; i < kMeans->k; ++i) {
        for (uint32_t j = 0; j < kMeans->dimension; ++j) {
            ((kMeans->centroids)[i].vector)[j] = (int64_t) 0;
        }
    }
    for (uint32_t i = 0; i < kMeans->k; ++i) {
        (kMeans->clustersSize)[i] = (uint64_t) 0;
    }
    // Sum
    for (uint64_t i = 0; i < kMeans->size; ++i) {
        uint32_t centroidID = (kMeans->points)[i].nearestCentroidID;
        for (uint32_t j = 0; j < kMeans->dimension; ++j) {
            ((kMeans->centroids)[centroidID].vector)[j] += ((kMeans->points)[i].vector)[j];
        }
        (kMeans->clustersSize)[centroidID]++;
    }
    // Computing the average
    for (uint32_t i = 0; i < kMeans->k; ++i) {
        for (uint32_t j = 0; j < kMeans->dimension; ++j) {
            /** Comments from the python script:
            /!\ we here use int(a/b) instead of a//b because // implements the floor division and with negative
             # numbers this is not an integer division as it rounds the result down */
            ((kMeans->centroids)[i].vector)[j] = ((kMeans->centroids)[i].vector)[j] /
                                                 (int64_t) (kMeans->clustersSize)[i];
        }
    }
}

int32_t assignVectorsToCentroids(kMeans_t *kMeans,
                                 squared_distance_func_t distanceFunction(const point_t *, const point_t *,
                                                                          uint32_t)) {
    int32_t hasChanged = 0;
    squared_distance_func_t genericDistanceFunction = (squared_distance_func_t) distanceFunction;
    for (uint64_t i = 0; i < kMeans->size; ++i) {
        // Let's find the closest centroid
        uint64_t currentDistance = genericDistanceFunction(&(kMeans->points)[i], &(kMeans->centroids)[0],
                                                           kMeans->dimension);;
        uint32_t currentCentroid = 0;
        uint32_t oldCentroid = (kMeans->points)[i].nearestCentroidID;
        for (uint32_t j = 1; j < kMeans->k; ++j) {
            uint64_t newDistance = genericDistanceFunction(&(kMeans->points)[i], &(kMeans->centroids)[j],
                                                           kMeans->dimension);
            if (newDistance < currentDistance) {
                currentDistance = newDistance;
                currentCentroid = j;
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
    kMeans->clustersSize = (uint64_t *) malloc(k * sizeof(uint64_t));
    if (kMeans->clustersSize == NULL) return NULL;
    kMeans->points = (point_t *) malloc(size * sizeof(point_t));
    if (kMeans->points == NULL) return NULL;
    kMeans->centroids = (point_t *) malloc(k * sizeof(point_t));
    if (kMeans->centroids == NULL) return NULL;

    kMeans->k = k;
    kMeans->size = size;
    kMeans->dimension = dimension;

    // setup centroids
    for (uint32_t i = 0; i < k; ++i) {
        (kMeans->centroids)[i].vector = (int64_t *) malloc(dimension * sizeof(int64_t));
        if ((kMeans->centroids)[i].vector == NULL) return NULL;
        for (uint32_t j = 0; j < dimension; ++j) {
            (kMeans->centroids)[i].vector[j] = (startingCentroidsID[index][i].vector)[j];
        }
    }
    // setup points
    for (uint64_t i = 0; i < size; ++i) {
        (kMeans->points)[i].vector = vectors[i];
        // By default all the points are allocated to the first centroid
        (kMeans->points)[i].nearestCentroidID = 0;
    }
    return kMeans;
}

uint64_t distortion(kMeans_t *kMeans, squared_distance_func_t
distanceFunction(const point_t *p1, const point_t *p2, uint32_t dimension)) {

    uint64_t distortionSum = 0;
    squared_distance_func_t genericDistanceFunction = (squared_distance_func_t) distanceFunction;
    for (uint64_t i = 0; i < kMeans->size; ++i) {
        distortionSum += genericDistanceFunction(&(kMeans->points)[i],
                                                 &(kMeans->centroids)[((kMeans->points)[i]).nearestCentroidID],
                                                 kMeans->dimension);
    }
    return distortionSum;
}




