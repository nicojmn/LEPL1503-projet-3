#ifndef K_MEANS
#define K_MEANS

#include "point.h"

typedef struct {
    point_t *centroids;
    uint32_t k;
    point_t *points;
    uint32_t dimension;
    int64_t size;
} k_means_t;


/**
 * @param kMeans: pointer to the instance of our problem
 *        It assigns each point to its closest cluster
 */
void updateCentroids(k_means_t *kMeans);


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
                                 int64_t *distanceFunction(const point_t *, const point_t *, int32_t));


#endif //K_MEANS
