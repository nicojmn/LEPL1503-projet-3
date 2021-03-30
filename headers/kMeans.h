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


/** Be careful this has not been tested yet */
// TODO : write docstring
/**
 *
 * @param clusters
 * @param clusterNumber
 * @param dimension
 */
void updateCentroids(k_means_t *kMeans);


/**
 *
 * @param kMeans : the instance of the problem
 * @param distanceFunction : generic function to determine if we want manhattan or euclidean distance
 *
 * @return true if the assignation has changed from the last iteration
 *          + assigns the points to the closest cluster
 */
int32_t assignVectorsToCentroids(k_means_t *kMeans,
                                 int64_t *distanceFunction(const point_t *, const point_t *, int32_t));


#endif //K_MEANS
