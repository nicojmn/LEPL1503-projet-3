#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/kMeansTests.h"

kMeans_t *testsKMeansDim2 = NULL;
kMeans_t *testsKMeansDim3 = NULL;

int32_t kMeansSetup(void) {
    testsKMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (testsKMeansDim2 == NULL) return -1;
    testsKMeansDim2->dimension = (int32_t) 2;
    testsKMeansDim2->points = (point_t *) malloc(5 * sizeof(point_t));
    testsKMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (testsKMeansDim2->points == NULL) return -1;
    testsKMeansDim2->size = 3;
    testsKMeansDim2->k = 2;
    testsKMeansDim2->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (testsKMeansDim2->clustersSize == NULL) return -1;

    testsKMeansDim3 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (testsKMeansDim3 == NULL) return -1;
    testsKMeansDim3->dimension = (int32_t) 3;
    testsKMeansDim3->points = (point_t *) malloc(6 * sizeof(point_t));
    testsKMeansDim3->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (testsKMeansDim3->points == NULL) return -1;
    testsKMeansDim3->size = 6;
    testsKMeansDim3->k = 2;
    testsKMeansDim3->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (testsKMeansDim3->clustersSize == NULL) return -1;

    (testsKMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((testsKMeansDim2->points)[0].vector == NULL) return -1;
    ((testsKMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((testsKMeansDim2->points)[0].vector)[1] = (int64_t) 2;
    (testsKMeansDim2->points)[0].nearestCentroidID = 0;


    (testsKMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((testsKMeansDim2->points)[1].vector == NULL) return -1;
    ((testsKMeansDim2->points)[1].vector)[0] = (int64_t) -1;
    ((testsKMeansDim2->points)[1].vector)[1] = (int64_t) 4;
    (testsKMeansDim2->points)[1].nearestCentroidID = 0;

    (testsKMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((testsKMeansDim2->points)[2].vector == NULL) return -1;
    ((testsKMeansDim2->points)[2].vector)[0] = (int64_t) -4;
    ((testsKMeansDim2->points)[2].vector)[1] = (int64_t) 10;
    (testsKMeansDim2->points)[2].nearestCentroidID = 1;

    (testsKMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((testsKMeansDim2->centroids)[0].vector == NULL) return -1;
    ((testsKMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((testsKMeansDim2->centroids)[0].vector)[1] = (int64_t) 2;

    (testsKMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((testsKMeansDim2->centroids)[1].vector == NULL) return -1;
    ((testsKMeansDim2->centroids)[1].vector)[0] = (int64_t) -3;
    ((testsKMeansDim2->centroids)[1].vector)[1] = (int64_t) 9;

    (testsKMeansDim3->points)[0].vector = malloc(3 * sizeof(int64_t));
    if ((testsKMeansDim3->points)[0].vector == NULL) return -1;
    ((testsKMeansDim3->points)[0].vector)[0] = (int64_t) -1;
    ((testsKMeansDim3->points)[0].vector)[1] = (int64_t) 4;
    ((testsKMeansDim3->points)[0].vector)[2] = (int64_t) 4;
    (testsKMeansDim3->points)[0].nearestCentroidID = 0;

    (testsKMeansDim3->points)[1].vector = malloc(3 * sizeof(int64_t));
    if ((testsKMeansDim3->points)[1].vector == NULL) return -1;
    ((testsKMeansDim3->points)[1].vector)[0] = (int64_t) -1;
    ((testsKMeansDim3->points)[1].vector)[1] = (int64_t) -2;
    ((testsKMeansDim3->points)[1].vector)[2] = (int64_t) 9;
    (testsKMeansDim3->points)[1].nearestCentroidID = 0;

    (testsKMeansDim3->points)[2].vector = malloc(3 * sizeof(int64_t));
    if ((testsKMeansDim3->points)[2].vector == NULL) return -1;
    ((testsKMeansDim3->points)[2].vector)[0] = (int64_t) 2;
    ((testsKMeansDim3->points)[2].vector)[1] = (int64_t) 4;
    ((testsKMeansDim3->points)[2].vector)[2] = (int64_t) 2;
    (testsKMeansDim3->points)[2].nearestCentroidID = 0;

    (testsKMeansDim3->points)[3].vector = malloc(3 * sizeof(int64_t));
    if ((testsKMeansDim3->points)[3].vector == NULL) return -1;
    ((testsKMeansDim3->points)[3].vector)[0] = (int64_t) 6;
    ((testsKMeansDim3->points)[3].vector)[1] = (int64_t) 2;
    ((testsKMeansDim3->points)[3].vector)[2] = (int64_t) 1;
    (testsKMeansDim3->points)[3].nearestCentroidID = 1;

    (testsKMeansDim3->points)[4].vector = malloc(3 * sizeof(int64_t));
    if ((testsKMeansDim3->points)[4].vector == NULL) return -1;
    ((testsKMeansDim3->points)[4].vector)[0] = (int64_t) -2;
    ((testsKMeansDim3->points)[4].vector)[1] = (int64_t) 4;
    ((testsKMeansDim3->points)[4].vector)[2] = (int64_t) 3;
    (testsKMeansDim3->points)[4].nearestCentroidID = 1;

    (testsKMeansDim3->points)[5].vector = malloc(3 * sizeof(int64_t));
    if ((testsKMeansDim3->points)[5].vector == NULL) return -1;
    ((testsKMeansDim3->points)[5].vector)[0] = (int64_t) 5;
    ((testsKMeansDim3->points)[5].vector)[1] = (int64_t) 5;
    ((testsKMeansDim3->points)[5].vector)[2] = (int64_t) 5;
    (testsKMeansDim3->points)[5].nearestCentroidID = 1;

    (testsKMeansDim3->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((testsKMeansDim3->centroids)[0].vector == NULL) return -1;
    ((testsKMeansDim3->centroids)[0].vector)[0] = (int64_t) -2;
    ((testsKMeansDim3->centroids)[0].vector)[1] = (int64_t) 4;
    ((testsKMeansDim3->centroids)[0].vector)[1] = (int64_t) 3;

    (testsKMeansDim3->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((testsKMeansDim3->centroids)[1].vector == NULL) return -1;
    ((testsKMeansDim3->centroids)[1].vector)[0] = (int64_t) 6;
    ((testsKMeansDim3->centroids)[1].vector)[1] = (int64_t) 2;
    ((testsKMeansDim3->centroids)[0].vector)[1] = (int64_t) 1;
    return 0;
}

int32_t kMeansTeardown(void) {
    free((testsKMeansDim2->points)[0].vector);
    free((testsKMeansDim2->points)[1].vector);
    free((testsKMeansDim2->points)[2].vector);
    free((testsKMeansDim2->centroids)[0].vector);
    free((testsKMeansDim2->centroids)[1].vector);
    free(testsKMeansDim2->points);
    free(testsKMeansDim2->centroids);
    free(testsKMeansDim2->clustersSize);
    free(testsKMeansDim2);
    free((testsKMeansDim3->points)[0].vector);
    free((testsKMeansDim3->points)[1].vector);
    free((testsKMeansDim3->points)[2].vector);
    free((testsKMeansDim3->points)[3].vector);
    free((testsKMeansDim3->points)[4].vector);
    free((testsKMeansDim3->points)[5].vector);
    free((testsKMeansDim3->centroids)[0].vector);
    free((testsKMeansDim3->centroids)[1].vector);
    free(testsKMeansDim3->points);
    free((testsKMeansDim3->centroids));
    free(testsKMeansDim3->clustersSize);
    free(testsKMeansDim3);
    return 0;
}

/** Testing with different dimensions
    We've used the corresponding python function to get the correct value
*/
void testKmeansDimension2(void) {
    squared_distance_func_t generic_func = squared_euclidean_distance;
    runKMeans(testsKMeansDim2, (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                            uint32_t)) generic_func);


    //centroid
    CU_ASSERT_EQUAL((testsKMeansDim2->centroids)[0].vector[0], (int64_t) 0);
    CU_ASSERT_EQUAL((testsKMeansDim2->centroids)[0].vector[1], (int64_t) 3);
    CU_ASSERT_EQUAL((testsKMeansDim2->centroids)[1].vector[0], (int64_t) -4);
    CU_ASSERT_EQUAL((testsKMeansDim2->centroids)[1].vector[1], (int64_t) 10);

    //cluster
    CU_ASSERT_EQUAL((testsKMeansDim2->points)[0].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((testsKMeansDim2->points)[1].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((testsKMeansDim2->points)[2].nearestCentroidID, 1);
}