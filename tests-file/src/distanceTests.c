#include <CUnit/CUnit.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/tests.h"
#include "../headers/distanceTests.h"

kMeans_t *distanceKMeansDim1 = NULL;
kMeans_t *distanceKMeansDim2 = NULL;
kMeans_t *distanceKMeansDim3 = NULL;

int32_t distanceSetup(void) {
    distanceKMeansDim1 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (distanceKMeansDim1 == NULL) return -1;
    distanceKMeansDim1->dimension = (int32_t) 1;
    distanceKMeansDim1->points = (point_t *) malloc(1 * sizeof(point_t));
    if (distanceKMeansDim1->points == NULL) return -1;


    distanceKMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (distanceKMeansDim2 == NULL) return -1;
    distanceKMeansDim2->dimension = (int32_t) 2;
    distanceKMeansDim2->points = (point_t *) malloc(5 * sizeof(point_t));
    distanceKMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (distanceKMeansDim2->points == NULL) return -1;
    distanceKMeansDim2->size = 3;
    distanceKMeansDim2->k = 2;
    distanceKMeansDim2->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (distanceKMeansDim2->clustersSize == NULL) return -1;

    distanceKMeansDim3 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (distanceKMeansDim3 == NULL) return -1;
    distanceKMeansDim3->dimension = (int32_t) 3;
    distanceKMeansDim3->points = (point_t *) malloc(6 * sizeof(point_t));
    distanceKMeansDim3->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (distanceKMeansDim3->points == NULL) return -1;
    distanceKMeansDim3->size = 6;
    distanceKMeansDim3->k = 2;
    distanceKMeansDim3->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (distanceKMeansDim3->clustersSize == NULL) return -1;

    (distanceKMeansDim1->points)[0].vector = malloc(1 * sizeof(int64_t));
    if ((distanceKMeansDim1->points)[0].vector == NULL) return -1;
    ((distanceKMeansDim1->points)[0].vector)[0] = (int64_t) 1;

    (distanceKMeansDim1->points)[1].vector = malloc(1 * sizeof(int64_t));
    if ((distanceKMeansDim1->points)[1].vector == NULL) return -1;
    ((distanceKMeansDim1->points)[1].vector)[0] = (int64_t) 2;

    (distanceKMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((distanceKMeansDim2->points)[0].vector == NULL) return -1;
    ((distanceKMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((distanceKMeansDim2->points)[0].vector)[1] = (int64_t) 2;
    (distanceKMeansDim2->points)[0].nearestCentroidID = 0;


    (distanceKMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((distanceKMeansDim2->points)[1].vector == NULL) return -1;
    ((distanceKMeansDim2->points)[1].vector)[0] = (int64_t) -1;
    ((distanceKMeansDim2->points)[1].vector)[1] = (int64_t) 4;
    (distanceKMeansDim2->points)[1].nearestCentroidID = 0;

    (distanceKMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((distanceKMeansDim2->points)[2].vector == NULL) return -1;
    ((distanceKMeansDim2->points)[2].vector)[0] = (int64_t) -4;
    ((distanceKMeansDim2->points)[2].vector)[1] = (int64_t) 10;
    (distanceKMeansDim2->points)[2].nearestCentroidID = 1;

    (distanceKMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((distanceKMeansDim2->centroids)[0].vector == NULL) return -1;
    ((distanceKMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((distanceKMeansDim2->centroids)[0].vector)[1] = (int64_t) 2;

    (distanceKMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((distanceKMeansDim2->centroids)[1].vector == NULL) return -1;
    ((distanceKMeansDim2->centroids)[1].vector)[0] = (int64_t) -3;
    ((distanceKMeansDim2->centroids)[1].vector)[1] = (int64_t) 9;

    (distanceKMeansDim3->points)[0].vector = malloc(3 * sizeof(int64_t));
    if ((distanceKMeansDim3->points)[0].vector == NULL) return -1;
    ((distanceKMeansDim3->points)[0].vector)[0] = (int64_t) -1;
    ((distanceKMeansDim3->points)[0].vector)[1] = (int64_t) 4;
    ((distanceKMeansDim3->points)[0].vector)[2] = (int64_t) 4;
    (distanceKMeansDim3->points)[0].nearestCentroidID = 0;

    (distanceKMeansDim3->points)[1].vector = malloc(3 * sizeof(int64_t));
    if ((distanceKMeansDim3->points)[1].vector == NULL) return -1;
    ((distanceKMeansDim3->points)[1].vector)[0] = (int64_t) -1;
    ((distanceKMeansDim3->points)[1].vector)[1] = (int64_t) -2;
    ((distanceKMeansDim3->points)[1].vector)[2] = (int64_t) 9;
    (distanceKMeansDim3->points)[1].nearestCentroidID = 0;

    (distanceKMeansDim3->points)[2].vector = malloc(3 * sizeof(int64_t));
    if ((distanceKMeansDim3->points)[2].vector == NULL) return -1;
    ((distanceKMeansDim3->points)[2].vector)[0] = (int64_t) 2;
    ((distanceKMeansDim3->points)[2].vector)[1] = (int64_t) 4;
    ((distanceKMeansDim3->points)[2].vector)[2] = (int64_t) 2;
    (distanceKMeansDim3->points)[2].nearestCentroidID = 0;

    (distanceKMeansDim3->points)[3].vector = malloc(3 * sizeof(int64_t));
    if ((distanceKMeansDim3->points)[3].vector == NULL) return -1;
    ((distanceKMeansDim3->points)[3].vector)[0] = (int64_t) 6;
    ((distanceKMeansDim3->points)[3].vector)[1] = (int64_t) 2;
    ((distanceKMeansDim3->points)[3].vector)[2] = (int64_t) 1;
    (distanceKMeansDim3->points)[3].nearestCentroidID = 1;

    (distanceKMeansDim3->points)[4].vector = malloc(3 * sizeof(int64_t));
    if ((distanceKMeansDim3->points)[4].vector == NULL) return -1;
    ((distanceKMeansDim3->points)[4].vector)[0] = (int64_t) -2;
    ((distanceKMeansDim3->points)[4].vector)[1] = (int64_t) 4;
    ((distanceKMeansDim3->points)[4].vector)[2] = (int64_t) 3;
    (distanceKMeansDim3->points)[4].nearestCentroidID = 1;

    (distanceKMeansDim3->points)[5].vector = malloc(3 * sizeof(int64_t));
    if ((distanceKMeansDim3->points)[5].vector == NULL) return -1;
    ((distanceKMeansDim3->points)[5].vector)[0] = (int64_t) 5;
    ((distanceKMeansDim3->points)[5].vector)[1] = (int64_t) 5;
    ((distanceKMeansDim3->points)[5].vector)[2] = (int64_t) 5;
    (distanceKMeansDim3->points)[5].nearestCentroidID = 1;

    (distanceKMeansDim3->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((distanceKMeansDim3->centroids)[0].vector == NULL) return -1;
    ((distanceKMeansDim3->centroids)[0].vector)[0] = (int64_t) -2;
    ((distanceKMeansDim3->centroids)[0].vector)[1] = (int64_t) 4;
    ((distanceKMeansDim3->centroids)[0].vector)[1] = (int64_t) 3;

    (distanceKMeansDim3->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((distanceKMeansDim3->centroids)[1].vector == NULL) return -1;
    ((distanceKMeansDim3->centroids)[1].vector)[0] = (int64_t) 6;
    ((distanceKMeansDim3->centroids)[1].vector)[1] = (int64_t) 2;
    ((distanceKMeansDim3->centroids)[0].vector)[1] = (int64_t) 1;
    return 0;
}

int32_t distanceTeardown(void) {
    free((distanceKMeansDim1->points)[0].vector);
    free((distanceKMeansDim1->points)[1].vector);
    free(distanceKMeansDim1->points);
    free(distanceKMeansDim1->clustersSize);
    free(distanceKMeansDim1);
    free((distanceKMeansDim2->points)[0].vector);
    free((distanceKMeansDim2->points)[1].vector);
    free((distanceKMeansDim2->points)[2].vector);
    free((distanceKMeansDim2->centroids)[0].vector);
    free((distanceKMeansDim2->centroids)[1].vector);
    free(distanceKMeansDim2->points);
    free(distanceKMeansDim2->centroids);
    free(distanceKMeansDim2->clustersSize);
    free(distanceKMeansDim2);
    free((distanceKMeansDim3->points)[0].vector);
    free((distanceKMeansDim3->points)[1].vector);
    free((distanceKMeansDim3->points)[2].vector);
    free((distanceKMeansDim3->points)[3].vector);
    free((distanceKMeansDim3->points)[4].vector);
    free((distanceKMeansDim3->points)[5].vector);
    free((distanceKMeansDim3->centroids)[0].vector);
    free((distanceKMeansDim3->centroids)[1].vector);
    free(distanceKMeansDim3->points);
    free((distanceKMeansDim3->centroids));
    free(distanceKMeansDim3->clustersSize);
    free(distanceKMeansDim3);
    return 0;
}

/** We've used the corresponding python function to get the correct value */
void testManhattan(void) {
    CU_ASSERT_EQUAL(squared_manhattan_distance(&distanceKMeansDim1->points[0], &distanceKMeansDim1->points[1],
                                               distanceKMeansDim1->dimension), 1);
    CU_ASSERT_EQUAL(squared_manhattan_distance(&distanceKMeansDim2->points[0], &distanceKMeansDim2->points[1],
                                               distanceKMeansDim2->dimension), 16);
    CU_ASSERT_EQUAL(squared_manhattan_distance(&distanceKMeansDim3->points[0], &distanceKMeansDim3->points[1],
                                               distanceKMeansDim3->dimension), 121);
}

/** We've used the corresponding python function to get the corrects values */
void testEuclidean(void) {
    CU_ASSERT_EQUAL(squared_euclidean_distance(&distanceKMeansDim1->points[0], &distanceKMeansDim1->points[1],
                                               distanceKMeansDim1->dimension), 1);
    CU_ASSERT_EQUAL(squared_euclidean_distance(&distanceKMeansDim2->points[0], &distanceKMeansDim2->points[1],
                                               distanceKMeansDim2->dimension), 8);
    CU_ASSERT_EQUAL(squared_euclidean_distance(&distanceKMeansDim3->points[0], &distanceKMeansDim3->points[1],
                                               distanceKMeansDim3->dimension), 61);
}
