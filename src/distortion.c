#include "../headers/distortion.h"

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

