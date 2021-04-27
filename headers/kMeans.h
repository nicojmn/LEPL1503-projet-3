#ifndef K_MEANS
#define K_MEANS

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>

#include "kmeansStruct.h"
#include "distance.h"

/**
 * @param kMeans: pointer to the instance of our problem
 *        It assigns each kmeansStruct to its closest cluster and update the size of each cluster
 */
void updateCentroids(kMeans_t *kMeans);

/**
 *
 * @param kMeans : the instance of the problem
 * @param distanceFunction : generic function which correspond to manhattan or euclidean distance function
 *                           depending on the choice of the user
 *
 * @return true if the assignation has changed from the last iteration
 *          + assigns the points to the closest cluster
 */
int32_t assignVectorsToCentroids(kMeans_t *kMeans,
                                 squared_distance_func_t distanceFunction(const point_t *, const point_t *,
                                                                          uint32_t));

/**
 *
 * @param kMeans : the instance of the problem
 * @param distanceFunction : generic function which correspond to manhattan or euclidean distance function
 *                           depending on the choice of the user
 */
void runKMeans(kMeans_t *kMeans,
               squared_distance_func_t distanceFunction(const point_t *, const point_t *,
                                                        uint32_t));

// TODO: Comments
kMeans_t *createOneInstance(int64_t **vectors, point_t **startingCentroidsID, uint32_t index, uint32_t k,
                            uint64_t size, uint32_t dimension);

// TODO: Comments
uint64_t distortion(kMeans_t *kMeans, squared_distance_func_t
distanceFunction(const point_t *p1, const point_t *p2, uint32_t dimension));

#endif
