#include <CUnit/CUnit.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/assignVectorTests.h"

kMeans_t *assignVectorkMeansDim2 = NULL;

int32_t assignVectorSetup(void) {
    assignVectorkMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (assignVectorkMeansDim2 == NULL) return -1;
    assignVectorkMeansDim2->dimension = (int32_t) 2;
    assignVectorkMeansDim2->points = (point_t *) malloc(5 * sizeof(point_t));
    assignVectorkMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (assignVectorkMeansDim2->points == NULL) return -1;
    assignVectorkMeansDim2->size = 3;
    assignVectorkMeansDim2->k = 2;
    assignVectorkMeansDim2->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (assignVectorkMeansDim2->clustersSize == NULL) return -1;

    (assignVectorkMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorkMeansDim2->points)[0].vector == NULL) return -1;
    ((assignVectorkMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((assignVectorkMeansDim2->points)[0].vector)[1] = (int64_t) 2;
    (assignVectorkMeansDim2->points)[0].nearestCentroidID = 0;


    (assignVectorkMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorkMeansDim2->points)[1].vector == NULL) return -1;
    ((assignVectorkMeansDim2->points)[1].vector)[0] = (int64_t) -1;
    ((assignVectorkMeansDim2->points)[1].vector)[1] = (int64_t) 4;
    (assignVectorkMeansDim2->points)[1].nearestCentroidID = 0;

    (assignVectorkMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorkMeansDim2->points)[2].vector == NULL) return -1;
    ((assignVectorkMeansDim2->points)[2].vector)[0] = (int64_t) -4;
    ((assignVectorkMeansDim2->points)[2].vector)[1] = (int64_t) 10;
    (assignVectorkMeansDim2->points)[2].nearestCentroidID = 1;

    (assignVectorkMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorkMeansDim2->centroids)[0].vector == NULL) return -1;
    ((assignVectorkMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((assignVectorkMeansDim2->centroids)[0].vector)[1] = (int64_t) 2;

    (assignVectorkMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((assignVectorkMeansDim2->centroids)[1].vector == NULL) return -1;
    ((assignVectorkMeansDim2->centroids)[1].vector)[0] = (int64_t) -3;
    ((assignVectorkMeansDim2->centroids)[1].vector)[1] = (int64_t) 9;

    return 0;
}

int32_t assignVectorTeardown(void) {
    free((assignVectorkMeansDim2->points)[0].vector);
    free((assignVectorkMeansDim2->points)[1].vector);
    free((assignVectorkMeansDim2->points)[2].vector);
    free((assignVectorkMeansDim2->centroids)[0].vector);
    free((assignVectorkMeansDim2->centroids)[1].vector);
    free(assignVectorkMeansDim2->points);
    free(assignVectorkMeansDim2->centroids);
    free(assignVectorkMeansDim2->clustersSize);
    free(assignVectorkMeansDim2);
    return 0;
}

/** We've used the corresponding python function to get the correct value */
void testNormalAssignVectorToCentroids(void) {
    (assignVectorkMeansDim2->points)[1].nearestCentroidID = 1;

    squared_distance_func_t generic_func = squared_euclidean_distance;
    CU_ASSERT_TRUE(assignVectorsToCentroids(assignVectorkMeansDim2,
                                            (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                         uint32_t)) generic_func));

    CU_ASSERT_EQUAL((assignVectorkMeansDim2->points)[0].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((assignVectorkMeansDim2->points)[1].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((assignVectorkMeansDim2->points)[2].nearestCentroidID, 1);

    CU_ASSERT_FALSE(assignVectorsToCentroids(assignVectorkMeansDim2,
                                             (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                          uint32_t)) generic_func));
}

/** We've used the corresponding python function to get the correct value */
void testFirstAssignVectorToCentroids(void) {
    (assignVectorkMeansDim2->points)[0].nearestCentroidID = -1;
    (assignVectorkMeansDim2->points)[1].nearestCentroidID = -1;
    (assignVectorkMeansDim2->points)[2].nearestCentroidID = -1;

    squared_distance_func_t generic_func = squared_euclidean_distance;
    CU_ASSERT_TRUE(assignVectorsToCentroids(assignVectorkMeansDim2,
                                            (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                         uint32_t)) generic_func));

    CU_ASSERT_EQUAL((assignVectorkMeansDim2->points)[0].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((assignVectorkMeansDim2->points)[1].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((assignVectorkMeansDim2->points)[2].nearestCentroidID, 1);

    CU_ASSERT_FALSE(assignVectorsToCentroids(assignVectorkMeansDim2,
                                             (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                          uint32_t)) generic_func));
}