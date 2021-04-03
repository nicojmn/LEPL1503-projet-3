#ifndef K_MEANS
#define K_MEANS

#include "point.h"
#include "../headers/distance.h"

typedef struct {

    point_t *centroids;
    int64_t *clustersSize;
    uint32_t k;
    point_t *points;
    uint32_t dimension;
    uint64_t size;

} k_means_t;

typedef struct {
    int64_t **vectors;
    uint32_t dimension;
    uint64_t size;
} data_t;

/**
 * @param kMeans: pointer to the instance of our problem
 *        It assigns each point to its closest cluster and update the size of each cluster
 */
void updateCentroids(k_means_t *kMeans);

/** Copy function from distance.h */
typedef int64_t (*squared_distance_func_t)(const point_t *, const point_t *, int32_t);

/**
 *
 * @param kMeans : the instance of the problem
 * @param distanceFunction : generic function which correspond to manhattan or euclidean distance function
 *                           depending on the choice of the user
 *
 * @return true if the assignation has changed from the last iteration
 *          + assigns the points to the closest cluster
 */
int32_t assignVectorsToCentroids(k_means_t *kMeans,
                                 squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2,
                                                                          int32_t dimension));

/**
 *
 * @param kMeans : the instance of the problem
 * @param distanceFunction : generic function which correspond to manhattan or euclidean distance function
 *                           depending on the choice of the user
 *        It updates each cluster to match witch the nearest centroid
 */

void k_means(k_means_t *kMeans,
             squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2,
                                                      int32_t dimension));

k_means_t *produce(int64_t **vectors, point_t **startingCentroidsID, int32_t index, int32_t k,
                   int64_t size, uint32_t dimension);

void clean(k_means_t *KMeans);

#endif //K_MEANS
