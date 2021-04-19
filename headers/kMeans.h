#ifndef K_MEANS
#define K_MEANS

#include "kmeansStruct.h"
#include "distance.h"


/**
 * @param kMeans: pointer to the instance of our problem
 *        It assigns each kmeansStruct to its closest cluster and update the size of each cluster
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
                                 squared_distance_func_t distanceFunction(const point_t *, const point_t *,
                                                                          int32_t));

/**
 *
 * @param kMeans : the instance of the problem
 * @param distanceFunction : generic function which correspond to manhattan or euclidean distance function
 *                           depending on the choice of the user
 *        It updates each cluster to match witch the nearest centroid
 */

void k_means(k_means_t *kMeans,
             squared_distance_func_t distanceFunction(const point_t *, const point_t *,
                                                      int32_t));

k_means_t *createOneInstance(int64_t **vectors, point_t **startingCentroidsID, uint32_t index, uint32_t k,
                             uint64_t size, uint32_t dimension);

#endif
