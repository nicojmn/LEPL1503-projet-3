#include "../headers/assignVectorTests.h"

kMeans_t *assignVectorKMeansDim2 = NULL;

/**
 * Creation of a simulation:
 *    - in 2 dimensions
 *    - 3 points: [(1, 2), (-1, 4), (-4, 10)]
 *    - 2 centroids: [(1, 2), (-4, 10)]
 */
int32_t assignVectorSetup(void) {
    assignVectorKMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (assignVectorKMeansDim2 == NULL) return -1;
    assignVectorKMeansDim2->dimension = (int32_t) 2;
    assignVectorKMeansDim2->points = (point_t *) malloc(3 * sizeof(point_t));
    if (assignVectorKMeansDim2->points == NULL) return -1;
    assignVectorKMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (assignVectorKMeansDim2->centroids == NULL) return -1;
    assignVectorKMeansDim2->size = 3;
    assignVectorKMeansDim2->k = 2;
    assignVectorKMeansDim2->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (assignVectorKMeansDim2->clustersSize == NULL) return -1;

    (assignVectorKMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorKMeansDim2->points)[0].vector == NULL) return -1;
    ((assignVectorKMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((assignVectorKMeansDim2->points)[0].vector)[1] = (int64_t) 2;
    (assignVectorKMeansDim2->points)[0].nearestCentroidID = 0;

    (assignVectorKMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorKMeansDim2->points)[1].vector == NULL) return -1;
    ((assignVectorKMeansDim2->points)[1].vector)[0] = (int64_t) -1;
    ((assignVectorKMeansDim2->points)[1].vector)[1] = (int64_t) 4;
    (assignVectorKMeansDim2->points)[1].nearestCentroidID = 0;

    (assignVectorKMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorKMeansDim2->points)[2].vector == NULL) return -1;
    ((assignVectorKMeansDim2->points)[2].vector)[0] = (int64_t) -4;
    ((assignVectorKMeansDim2->points)[2].vector)[1] = (int64_t) 10;
    (assignVectorKMeansDim2->points)[2].nearestCentroidID = 1;

    (assignVectorKMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorKMeansDim2->centroids)[0].vector == NULL) return -1;
    ((assignVectorKMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((assignVectorKMeansDim2->centroids)[0].vector)[1] = (int64_t) 2;

    (assignVectorKMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorKMeansDim2->centroids)[1].vector == NULL) return -1;
    ((assignVectorKMeansDim2->centroids)[1].vector)[0] = (int64_t) -3;
    ((assignVectorKMeansDim2->centroids)[1].vector)[1] = (int64_t) 9;

    return 0;
}

int32_t assignVectorTeardown(void) {
    free((assignVectorKMeansDim2->points)[0].vector);
    free((assignVectorKMeansDim2->points)[1].vector);
    free((assignVectorKMeansDim2->points)[2].vector);
    free((assignVectorKMeansDim2->centroids)[0].vector);
    free((assignVectorKMeansDim2->centroids)[1].vector);
    free(assignVectorKMeansDim2->points);
    free(assignVectorKMeansDim2->centroids);
    free(assignVectorKMeansDim2->clustersSize);
    free(assignVectorKMeansDim2);
    return 0;
}

/** We've used the corresponding python function to get the correct value */
void testNormalAssignVectorToCentroids(void) {

    // We make a change
    (assignVectorKMeansDim2->points)[1].nearestCentroidID = 1;

    squared_distance_func_t generic_func = squared_euclidean_distance;
    CU_ASSERT_TRUE(assignVectorsToCentroids(assignVectorKMeansDim2,
                                            (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                         uint32_t)) generic_func));

    CU_ASSERT_EQUAL((assignVectorKMeansDim2->points)[0].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((assignVectorKMeansDim2->points)[1].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((assignVectorKMeansDim2->points)[2].nearestCentroidID, 1);

    CU_ASSERT_FALSE(assignVectorsToCentroids(assignVectorKMeansDim2,
                                             (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                          uint32_t)) generic_func));
}

/** We've used the corresponding python function to get the correct value */
void testFirstAssignVectorToCentroids(void) {
    (assignVectorKMeansDim2->points)[0].nearestCentroidID = -1;
    (assignVectorKMeansDim2->points)[1].nearestCentroidID = -1;
    (assignVectorKMeansDim2->points)[2].nearestCentroidID = -1;

    squared_distance_func_t generic_func = squared_euclidean_distance;
    CU_ASSERT_TRUE(assignVectorsToCentroids(assignVectorKMeansDim2,
                                            (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                         uint32_t)) generic_func));

    CU_ASSERT_EQUAL((assignVectorKMeansDim2->points)[0].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((assignVectorKMeansDim2->points)[1].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((assignVectorKMeansDim2->points)[2].nearestCentroidID, 1);

    // Only one iteration is necessary to find a local minimum here so no change can occur
    CU_ASSERT_FALSE(assignVectorsToCentroids(assignVectorKMeansDim2,
                                             (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                          uint32_t)) generic_func));
}