#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/kMeansTests.h"


int32_t kMeansSetup(void) {
    kMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (kMeansDim2 == NULL) return -1;
    kMeansDim2->dimension = (int32_t) 2;
    kMeansDim2->points = (point_t *) malloc(5 * sizeof(point_t));
    kMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim2->points == NULL) return -1;
    kMeansDim2->size = 3;
    kMeansDim2->k = 2;
    kMeansDim2->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (kMeansDim2->clustersSize == NULL) return -1;

    kMeansDim3 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (kMeansDim3 == NULL) return -1;
    kMeansDim3->dimension = (int32_t) 3;
    kMeansDim3->points = (point_t *) malloc(6 * sizeof(point_t));
    kMeansDim3->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim3->points == NULL) return -1;
    kMeansDim3->size = 6;
    kMeansDim3->k = 2;
    kMeansDim3->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (kMeansDim3->clustersSize == NULL) return -1;

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

    (kMeansDim3->points)[0].vector = malloc(3 * sizeof(int64_t));
    if ((kMeansDim3->points)[0].vector == NULL) return -1;
    ((kMeansDim3->points)[0].vector)[0] = (int64_t) -1;
    ((kMeansDim3->points)[0].vector)[1] = (int64_t) 4;
    ((kMeansDim3->points)[0].vector)[2] = (int64_t) 4;
    (kMeansDim3->points)[0].nearestCentroidID = 0;

    (kMeansDim3->points)[1].vector = malloc(3 * sizeof(int64_t));
    if ((kMeansDim3->points)[1].vector == NULL) return -1;
    ((kMeansDim3->points)[1].vector)[0] = (int64_t) -1;
    ((kMeansDim3->points)[1].vector)[1] = (int64_t) -2;
    ((kMeansDim3->points)[1].vector)[2] = (int64_t) 9;
    (kMeansDim3->points)[1].nearestCentroidID = 0;

    (kMeansDim3->points)[2].vector = malloc(3 * sizeof(int64_t));
    if ((kMeansDim3->points)[2].vector == NULL) return -1;
    ((kMeansDim3->points)[2].vector)[0] = (int64_t) 2;
    ((kMeansDim3->points)[2].vector)[1] = (int64_t) 4;
    ((kMeansDim3->points)[2].vector)[2] = (int64_t) 2;
    (kMeansDim3->points)[2].nearestCentroidID = 0;

    (kMeansDim3->points)[3].vector = malloc(3 * sizeof(int64_t));
    if ((kMeansDim3->points)[3].vector == NULL) return -1;
    ((kMeansDim3->points)[3].vector)[0] = (int64_t) 6;
    ((kMeansDim3->points)[3].vector)[1] = (int64_t) 2;
    ((kMeansDim3->points)[3].vector)[2] = (int64_t) 1;
    (kMeansDim3->points)[3].nearestCentroidID = 1;

    (kMeansDim3->points)[4].vector = malloc(3 * sizeof(int64_t));
    if ((kMeansDim3->points)[4].vector == NULL) return -1;
    ((kMeansDim3->points)[4].vector)[0] = (int64_t) -2;
    ((kMeansDim3->points)[4].vector)[1] = (int64_t) 4;
    ((kMeansDim3->points)[4].vector)[2] = (int64_t) 3;
    (kMeansDim3->points)[4].nearestCentroidID = 1;

    (kMeansDim3->points)[5].vector = malloc(3 * sizeof(int64_t));
    if ((kMeansDim3->points)[5].vector == NULL) return -1;
    ((kMeansDim3->points)[5].vector)[0] = (int64_t) 5;
    ((kMeansDim3->points)[5].vector)[1] = (int64_t) 5;
    ((kMeansDim3->points)[5].vector)[2] = (int64_t) 5;
    (kMeansDim3->points)[5].nearestCentroidID = 1;

    (kMeansDim3->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim3->centroids)[0].vector == NULL) return -1;
    ((kMeansDim3->centroids)[0].vector)[0] = (int64_t) -2;
    ((kMeansDim3->centroids)[0].vector)[1] = (int64_t) 4;
    ((kMeansDim3->centroids)[0].vector)[1] = (int64_t) 3;

    (kMeansDim3->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim3->centroids)[1].vector == NULL) return -1;
    ((kMeansDim3->centroids)[1].vector)[0] = (int64_t) 6;
    ((kMeansDim3->centroids)[1].vector)[1] = (int64_t) 2;
    ((kMeansDim3->centroids)[0].vector)[1] = (int64_t) 1;
    return 0;
}

int32_t kMeansTeardown(void) {
    free((kMeansDim2->points)[0].vector);
    free((kMeansDim2->points)[1].vector);
    free((kMeansDim2->points)[2].vector);
    free((kMeansDim2->centroids)[0].vector);
    free((kMeansDim2->centroids)[1].vector);
    free(kMeansDim2->points);
    free(kMeansDim2->centroids);
    free(kMeansDim2->clustersSize);
    free(kMeansDim2);
    free((kMeansDim3->points)[0].vector);
    free((kMeansDim3->points)[1].vector);
    free((kMeansDim3->points)[2].vector);
    free((kMeansDim3->points)[3].vector);
    free((kMeansDim3->points)[4].vector);
    free((kMeansDim3->points)[5].vector);
    free((kMeansDim3->centroids)[0].vector);
    free((kMeansDim3->centroids)[1].vector);
    free(kMeansDim3->points);
    free((kMeansDim3->centroids));
    free(kMeansDim3->clustersSize);
    free(kMeansDim3);
    return 0;
}

/** Testing with different dimensions
    We've used the corresponding python function to get the correct value
*/
void testKmeansDimension2(void) {
    squared_distance_func_t generic_func = squared_euclidean_distance;
    runKMeans(kMeansDim2, (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                       uint32_t)) generic_func);


    //centroid
    CU_ASSERT_EQUAL((kMeansDim2->centroids)[0].vector[0], (int64_t) 0);
    CU_ASSERT_EQUAL((kMeansDim2->centroids)[0].vector[1], (int64_t) 3);
    CU_ASSERT_EQUAL((kMeansDim2->centroids)[1].vector[0], (int64_t) -4);
    CU_ASSERT_EQUAL((kMeansDim2->centroids)[1].vector[1], (int64_t) 10);

    //cluster
    CU_ASSERT_EQUAL((kMeansDim2->points)[0].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((kMeansDim2->points)[1].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((kMeansDim2->points)[2].nearestCentroidID, 1);
}