#ifndef K_MEANS
#define K_MEANS

#include "point.h"

typedef struct {
    centroid_t *centroids;
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
 * @param clusters : array of clusters
 * @param clustersSize : size of clusters
 * @param distanceFunction : generic function to determine if we want manhattan or euclidean distance
 * @param distanceMode : a string which contains "manhattan" or "euclidean"
 *
 * @return true if the assignation has changed from the last iteration
 */
int32_t assignVectorsToCentroids(centroid_t *centroids, uint32_t k,
                                 int64_t *distanceFunction(const point_t *, const point_t *, int32_t),
                                 char *distanceMode);


#endif //K_MEANS
