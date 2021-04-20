#include <CUnit/CUnit.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/assignVectorTests.h"

int32_t assignVectorSetup(void) {
    kMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (kMeansDim2 == NULL) return -1;
    kMeansDim2->dimension = (int32_t) 2;
    kMeansDim2->points = (point_t *) malloc(5 * sizeof(point_t));
    kMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim2->points == NULL) return -1;
    kMeansDim2->size = 3;
    kMeansDim2->k = 2;
    kMeansDim2->clustersSize = (int64_t *) malloc(2 * sizeof(int64_t *));
    if (kMeansDim2->clustersSize == NULL) return -1;

    (kMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[0].vector == NULL) return -1;
    ((kMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((kMeansDim2->points)[0].vector)[1] = (int64_t) 2;
    (kMeansDim2->points)[0].nearestCentroidID = 0;


    (kMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[1].vector == NULL) return -1;
    ((kMeansDim2->points)[1].vector)[0] = (int64_t) -1;
    ((kMeansDim2->points)[1].vector)[1] = (int64_t) 4;
    (kMeansDim2->points)[1].nearestCentroidID = 0;

    (kMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[2].vector == NULL) return -1;
    ((kMeansDim2->points)[2].vector)[0] = (int64_t) -4;
    ((kMeansDim2->points)[2].vector)[1] = (int64_t) 10;
    (kMeansDim2->points)[2].nearestCentroidID = 1;

    (kMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->centroids)[0].vector == NULL) return -1;
    ((kMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((kMeansDim2->centroids)[0].vector)[1] = (int64_t) 2;

    (kMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->centroids)[1].vector == NULL) return -1;
    ((kMeansDim2->centroids)[1].vector)[0] = (int64_t) -3;
    ((kMeansDim2->centroids)[1].vector)[1] = (int64_t) 9;

    return 0;
}

int32_t assignVectorTeardown(void) {
    free((kMeansDim2->points)[0].vector);
    free((kMeansDim2->points)[1].vector);
    free((kMeansDim2->points)[2].vector);
    free((kMeansDim2->centroids)[0].vector);
    free((kMeansDim2->centroids)[1].vector);
    free(kMeansDim2->points);
    free(kMeansDim2->centroids);
    free(kMeansDim2->clustersSize);
    free(kMeansDim2);
    return 0;
}

/** We've used the corresponding python function to get the correct value */
void testNormalAssignVectorToCentroids(void) {
    (kMeansDim2->points)[1].nearestCentroidID = 1;

    squared_distance_func_t generic_func = squared_euclidean_distance;
    CU_ASSERT_TRUE(assignVectorsToCentroids(kMeansDim2,
                                            (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                         int32_t)) generic_func));

    CU_ASSERT_EQUAL((kMeansDim2->points)[0].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((kMeansDim2->points)[1].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((kMeansDim2->points)[2].nearestCentroidID, 1);

    CU_ASSERT_FALSE(assignVectorsToCentroids(kMeansDim2,
                                             (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                          int32_t)) generic_func));
}

/** We've used the corresponding python function to get the correct value */
void testFirstAssignVectorToCentroids(void) {
    (kMeansDim2->points)[0].nearestCentroidID = -1;
    (kMeansDim2->points)[1].nearestCentroidID = -1;
    (kMeansDim2->points)[2].nearestCentroidID = -1;

    squared_distance_func_t generic_func = squared_euclidean_distance;
    CU_ASSERT_TRUE(assignVectorsToCentroids(kMeansDim2,
                                            (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                         int32_t)) generic_func));

    CU_ASSERT_EQUAL((kMeansDim2->points)[0].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((kMeansDim2->points)[1].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((kMeansDim2->points)[2].nearestCentroidID, 1);

    CU_ASSERT_FALSE(assignVectorsToCentroids(kMeansDim2,
                                             (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                          int32_t)) generic_func));
}