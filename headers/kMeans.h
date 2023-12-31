#ifndef K_MEANS
#define K_MEANS

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdint.h>

#include "kMeansStruct.h"
#include "distance.h"


/**
 * @param kMeans: pointer to the structure which gather all the information of our kMeans problem
 *        It calculates the new centroids' coordinates by computing the average
 *        of each dimension of the points from a specific cluster
 */
void updateCentroids(kMeans_t *kMeans);

/**
 * @param kMeans : pointer to the structure which gather all the information of our kMeans problem
 * @param distanceFunction : generic function which corresponds to manhattan or euclidean distance function
 *                           depending on the choice the user has made
 * @return : Assign each point to its closest cluster
 *           and return true if any point has changed its cluster
 */
int32_t assignVectorsToCentroids(kMeans_t *kMeans,
                                 squared_distance_func_t distanceFunction(const point_t *, const point_t *,
                                                                          uint32_t));

/**
 * @param kMeans : pointer to the structure which gather all the information of our kMeans problem
 * @param distanceFunction : generic function which corresponds to manhattan or euclidean distance function
 *                           depending on the choice the user has made
 */
void runKMeans(kMeans_t *kMeans,
               squared_distance_func_t distanceFunction(const point_t *, const point_t *,
                                                        uint32_t));

/**
 * @param vectors : the points of the simulation
 * @param startingCentroidsID : the different set of starting centroids
 * @param instanceIndex : the iteration instanceIndex (each iteration has an instanceIndex so that it can be linked
 *                                      to its set of starting centroids)
 * @param kCentroids : number of cluster
 * @param size : the number of points used by the simulation
 * @param dimension : the dimension of each point
 * @return : it returns the structure which will be used by our implementation of
 *           Lloyd's algorithm
 */
kMeans_t *
createOneInstance(int64_t **vectors, point_t **startingCentroidsID, uint32_t instanceIndex, uint32_t kCentroids,
                  uint64_t size, uint32_t dimension);

/**
 * @param kMeans: pointer to the structure which gather all the information of our kMeans problem
 * @param distanceFunction : generic function which corresponds to manhattan or euclidean distance function
 *                           depending on the choice the user has made
 * @return : the sum of all the distances between a point and its closest centroid
 */
uint64_t distortion(kMeans_t *kMeans,
                    squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2, uint32_t dimension));

#endif
