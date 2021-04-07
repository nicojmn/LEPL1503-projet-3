#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/distance.h"
#include "../../headers/point.h"
#include "../../headers/kMeans.h"
#include "../../src/distance.c"
#include "../../src/kMeans.c"
#include "../../src/generateStartingCentroids.c"
#include "../../headers/readBinaryFile.h"
#include "../../src/readBinaryFile.c"
#include "../../src/createOutputFile.c"

#include "../headers/tests.h"
#include "../headers/distanceTests.h"
#include "./distanceTests.c"
#include "../headers/readBinaryFileTests.h"
#include "./readBinaryFileTests.c"

// TODO refactor test.c in multiples files


/** Testing with different dimensions */

int32_t setup(void) {
    kMeansDim1 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim1 == NULL) return -1;
    kMeansDim1->dimension = (int32_t) 1;
    kMeansDim1->points = (point_t *) malloc(1 * sizeof(point_t));
    if (kMeansDim1->points == NULL) return -1;


    kMeansDim2 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim2 == NULL) return -1;
    kMeansDim2->dimension = (int32_t) 2;
    kMeansDim2->points = (point_t *) malloc(5 * sizeof(point_t));
    kMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim2->points == NULL) return -1;
    kMeansDim2->size = 3;
    kMeansDim2->k = 2;
    kMeansDim2->clustersSize = (int64_t *) malloc(2 * sizeof(int64_t *));
    if (kMeansDim2->clustersSize == NULL) return -1;

    kMeansDim3 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim3 == NULL) return -1;
    kMeansDim3->dimension = (int32_t) 3;
    kMeansDim3->points = (point_t *) malloc(6 * sizeof(point_t));
    kMeansDim3->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim3->points == NULL) return -1;
    kMeansDim3->size = 6;
    kMeansDim3->k = 2;
    kMeansDim3->clustersSize = (int64_t *) malloc(2 * sizeof(int64_t *));
    if (kMeansDim3->clustersSize == NULL) return -1;

    (kMeansDim1->points)[0].vector = malloc(1 * sizeof(int64_t));
    if ((kMeansDim1->points)[0].vector == NULL) return -1;
    ((kMeansDim1->points)[0].vector)[0] = (int64_t) 1;

    (kMeansDim1->points)[1].vector = malloc(1 * sizeof(int64_t));
    if ((kMeansDim1->points)[1].vector == NULL) return -1;
    ((kMeansDim1->points)[1].vector)[0] = (int64_t) 2;

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

int32_t teardown(void) {
    free((kMeansDim1->points)[0].vector);
    free((kMeansDim1->points)[1].vector);
    free(kMeansDim1->points);
    free(kMeansDim1->clustersSize);
    free(kMeansDim1);
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

int32_t setupCreateOutputfile(void) {
    kMeansDim2 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim2 == NULL) return -1;
    kMeansDim2->dimension = (int32_t) 2;
    kMeansDim2->points = (point_t *) malloc(7 * sizeof(point_t));
    kMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim2->points == NULL) return -1;
    kMeansDim2->size = 7;
    kMeansDim2->k = 2;
    kMeansDim2->clustersSize = (int64_t *) malloc(2 * sizeof(int64_t *));
    if (kMeansDim2->clustersSize == NULL) return -1;

    (kMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[0].vector == NULL) return -1;
    ((kMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((kMeansDim2->points)[0].vector)[1] = (int64_t) 1;
    (kMeansDim2->points)[0].nearestCentroidID = 0;


    (kMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[1].vector == NULL) return -1;
    ((kMeansDim2->points)[1].vector)[0] = (int64_t) 2;
    ((kMeansDim2->points)[1].vector)[1] = (int64_t) 2;
    (kMeansDim2->points)[1].nearestCentroidID = 1;

    (kMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[2].vector == NULL) return -1;
    ((kMeansDim2->points)[2].vector)[0] = (int64_t) 3;
    ((kMeansDim2->points)[2].vector)[1] = (int64_t) 4;
    (kMeansDim2->points)[2].nearestCentroidID = -1;

    (kMeansDim2->points)[3].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[3].vector == NULL) return -1;
    ((kMeansDim2->points)[3].vector)[0] = (int64_t) 5;
    ((kMeansDim2->points)[3].vector)[1] = (int64_t) 7;
    (kMeansDim2->points)[3].nearestCentroidID = -1;


    (kMeansDim2->points)[4].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[4].vector == NULL) return -1;
    ((kMeansDim2->points)[4].vector)[0] = (int64_t) 3;
    ((kMeansDim2->points)[4].vector)[1] = (int64_t) 5;
    (kMeansDim2->points)[4].nearestCentroidID = -1;

    (kMeansDim2->points)[5].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[5].vector == NULL) return -1;
    ((kMeansDim2->points)[5].vector)[0] = (int64_t) 5;
    ((kMeansDim2->points)[5].vector)[1] = (int64_t) 5;
    (kMeansDim2->points)[5].nearestCentroidID = -1;

    (kMeansDim2->points)[6].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[6].vector == NULL) return -1;
    ((kMeansDim2->points)[6].vector)[0] = (int64_t) 4;
    ((kMeansDim2->points)[6].vector)[1] = (int64_t) 5;
    (kMeansDim2->points)[6].nearestCentroidID = -1;


    (kMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->centroids)[0].vector == NULL) return -1;
    ((kMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((kMeansDim2->centroids)[0].vector)[1] = (int64_t) 1;

    (kMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->centroids)[1].vector == NULL) return -1;
    ((kMeansDim2->centroids)[1].vector)[0] = (int64_t) 2;
    ((kMeansDim2->centroids)[1].vector)[1] = (int64_t) 2;

    kMeansDim3 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim3 == NULL) return -1;
    kMeansDim3->dimension = (int32_t) 3;
    kMeansDim3->points = (point_t *) malloc(6 * sizeof(point_t));
    kMeansDim3->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim3->points == NULL) return -1;
    kMeansDim3->size = 6;
    kMeansDim3->k = 2;
    kMeansDim3->clustersSize = (int64_t *) malloc(2 * sizeof(int64_t *));
    if (kMeansDim3->clustersSize == NULL) return -1;

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

/** Testing output file */
FILE *outputFile;
FILE *outputFile2;
k_means_t *outputStartingCentroids1;
k_means_t *outputStartingCentroids2;

int32_t teardownCreateOutputFile(void) {
    free((kMeansDim2->points)[0].vector);
    free((kMeansDim2->points)[1].vector);
    free((kMeansDim2->points)[2].vector);
    free((kMeansDim2->points)[3].vector);
    free((kMeansDim2->points)[4].vector);
    free((kMeansDim2->points)[5].vector);
    free((kMeansDim2->points)[6].vector);

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

    free(outputFile);
    free(outputFile2);


    free(outputStartingCentroids1);
    free(outputStartingCentroids2);


    return 0;
}



/** We've used the corresponding python function to get the correct value */
void testDistortion(void) {
    squared_distance_func_t generic_func = squared_euclidean_distance;
    CU_ASSERT_EQUAL(distortion(kMeansDim2,
                               (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func),
                    10);
    generic_func = squared_manhattan_distance;
    CU_ASSERT_EQUAL(distortion(kMeansDim2,
                               (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func),
                    20);

}


/** We've used the corresponding python function to get the correct value */
void testUpdateCentroids(void) {
    updateCentroids(kMeansDim2);
    CU_ASSERT_EQUAL((kMeansDim2->centroids)[0].vector[0], (int64_t) 0);
    CU_ASSERT_EQUAL((kMeansDim2->centroids)[0].vector[1], (int64_t) 3);
    CU_ASSERT_EQUAL((kMeansDim2->centroids)[1].vector[0], (int64_t) -4);
    CU_ASSERT_EQUAL((kMeansDim2->centroids)[1].vector[1], (int64_t) 10);
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

void testKmeansDimension2(void) {
    squared_distance_func_t generic_func = squared_euclidean_distance;
    k_means(kMeansDim2, (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                     int32_t)) generic_func);


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

void testKmeansDimension3(void) {
    squared_distance_func_t generic_func = squared_euclidean_distance;
    k_means(kMeansDim3, (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                     int32_t)) generic_func);

    // Centroids
    CU_ASSERT_EQUAL((kMeansDim3->centroids)[0].vector[0], (int64_t) -1);
    CU_ASSERT_EQUAL((kMeansDim3->centroids)[0].vector[1], (int64_t) 2);
    CU_ASSERT_EQUAL((kMeansDim3->centroids)[0].vector[2], (int64_t) 5);

    CU_ASSERT_EQUAL((kMeansDim3->centroids)[1].vector[0], (int64_t) 4);
    CU_ASSERT_EQUAL((kMeansDim3->centroids)[1].vector[1], (int64_t) 3);
    CU_ASSERT_EQUAL((kMeansDim3->centroids)[1].vector[2], (int64_t) 2);

    //Clusters
    CU_ASSERT_EQUAL((kMeansDim3->points)[0].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((kMeansDim3->points)[1].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((kMeansDim3->points)[2].nearestCentroidID, 1);

    CU_ASSERT_EQUAL((kMeansDim3->points)[3].nearestCentroidID, 1);
    CU_ASSERT_EQUAL((kMeansDim3->points)[4].nearestCentroidID, 0);
    CU_ASSERT_EQUAL((kMeansDim3->points)[5].nearestCentroidID, 1);

    CU_ASSERT_EQUAL(kMeansDim3->clustersSize[0], 3);
    CU_ASSERT_EQUAL(kMeansDim3->clustersSize[1], 3);

}

void test_createOutputFileDimension3(void) {
    outputFile = fopen("output_csv/dimension3.csv", "w");
    printf("file opened\n");
    outputStartingCentroids1 = (k_means_t *) malloc(sizeof(point_t));
    squared_distance_func_t generic_func = squared_euclidean_distance;
    printf("\n%lu\n", kMeansDim3->points[0].vector[0]);
    k_means(kMeansDim3, (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);;
    printf("kmeans ok\n");

    outputStartingCentroids1->centroids = (point_t *) malloc(sizeof(point_t) * 2);
    outputStartingCentroids1->centroids[0].vector = malloc(sizeof(int64_t) * 3);

    outputStartingCentroids1->centroids[0].vector[0] = (int64_t) -2;
    outputStartingCentroids1->centroids[0].vector[1] = (int64_t) 4;
    outputStartingCentroids1->centroids[0].vector[2] = (int64_t) 3;

    outputStartingCentroids1->centroids[1].vector = malloc(sizeof(point_t) * 3);

    outputStartingCentroids1->centroids[1].vector[0] = (int64_t) 6;
    outputStartingCentroids1->centroids[1].vector[1] = (int64_t) 2;
    outputStartingCentroids1->centroids[1].vector[2] = (int64_t) 1;
    printf("malloced everything\n");
    csvFileHeadline(false, outputFile);
    printf("headline ok\n");

    writeOneKMeans(kMeansDim3, false, outputFile, outputStartingCentroids1->centroids,
                   (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);
    printf("kmeans ok\n");

}

void test_createOutputFileDimension2(void) {
    squared_distance_func_t generic_func = squared_manhattan_distance;
    outputFile2 = fopen("output_csv/ex1.csv", "w");
    outputStartingCentroids2 = (k_means_t *) malloc(sizeof(point_t));
    k_means(kMeansDim2, (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);

    outputStartingCentroids2->centroids = (point_t *) malloc(sizeof(point_t) * 2);
    outputStartingCentroids2->centroids[0].vector = malloc(sizeof(int64_t) * 2);

    outputStartingCentroids2->centroids[0].vector[0] = (int64_t) 1;
    outputStartingCentroids2->centroids[0].vector[1] = (int64_t) 1;

    outputStartingCentroids2->centroids[1].vector = malloc(sizeof(point_t) * 2);

    outputStartingCentroids2->centroids[1].vector[0] = (int64_t) 2;
    outputStartingCentroids2->centroids[1].vector[1] = (int64_t) 2;

    csvFileHeadline(false, outputFile2);
    writeOneKMeans(kMeansDim2, false, outputFile2, outputStartingCentroids2->centroids,
                   (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);
}

point_t **startingCentroids1;
point_t **startingCentroids2;

int32_t setupGenerateStartingCentroids(void) {

    dataTest1 = (data_t *) malloc(sizeof(data_t));
    if (dataTest1 == NULL) return -1;
    fileForTest1 = fopen("input_binary/ex1.bin", "r");
    loadData(fileForTest1, dataTest1);

    uint32_t k = 2;
    uint32_t n = 4;
    // We use a special function for numerical consideration
    // It won't overflow for close big number k and n
    uint64_t iterationNumber = combinatorial(n, k);
    startingCentroids1 = (point_t **) malloc(iterationNumber * sizeof(point_t *));
    for (uint64_t i = 0; i < iterationNumber; ++i) {
        startingCentroids1[i] = (point_t *) malloc(k * sizeof(point_t));
    }
    generateSetOfStartingCentroids(startingCentroids1, dataTest1->vectors, k, n, iterationNumber);

    dataTest2 = (data_t *) malloc(sizeof(data_t));
    if (dataTest2 == NULL) return -1;
    fileForTest2 = fopen("input_binary/ex3.bin", "r");
    loadData(fileForTest2, dataTest2);

    startingCentroids2 = (point_t **) malloc(iterationNumber * sizeof(point_t *));
    for (uint64_t i = 0; i < iterationNumber; ++i) {
        startingCentroids2[i] = (point_t *) malloc(k * sizeof(point_t));
    }
    generateSetOfStartingCentroids(startingCentroids2, dataTest2->vectors, k, n, iterationNumber);

    return 0;

}

int32_t teardownGenerateStartingCentroids(void) {

    if (0 != fclose(fileForTest1)) return -1;
    for (uint64_t i = 0; i < dataTest1->size; i++) {
        free((dataTest1->vectors)[i]);
    }

    free(dataTest1->vectors);
    free(dataTest1);

    if (0 != fclose(fileForTest2)) return -1;
    printf("%ld\n",dataTest2->size);
    for (uint64_t i = 0; i < dataTest2->size; i++) {
        free((dataTest2->vectors)[i]);
    }
    printf("datatest2\n");
    free(dataTest2->vectors);
    free(dataTest2);
    uint32_t k = 2;
    uint32_t n = 4;
    uint64_t iterationNumber = combinatorial(n, k);

    printf("startingcentroids\n");
    for (int i = 0; i < iterationNumber; ++i) {
        free(startingCentroids1[i]);
        free(startingCentroids2[i]);

    }
    free(startingCentroids1);
    free(startingCentroids2);

    return 0;
}

void testGenerateStartingCentroids(void) {

    //test : ex1.bin
    CU_ASSERT_EQUAL(startingCentroids1[0]->vector[0], 1);
    CU_ASSERT_EQUAL(startingCentroids1[0]->vector[1], 1);

    CU_ASSERT_EQUAL(startingCentroids1[1]->vector[0], 1);
    CU_ASSERT_EQUAL(startingCentroids1[1]->vector[1], 1);

    CU_ASSERT_EQUAL(startingCentroids1[2]->vector[0], 1);
    CU_ASSERT_EQUAL(startingCentroids1[2]->vector[1], 1);

    CU_ASSERT_EQUAL(startingCentroids1[3]->vector[0], 2);
    CU_ASSERT_EQUAL(startingCentroids1[3]->vector[1], 2);

    CU_ASSERT_EQUAL(startingCentroids1[4]->vector[0], 3);
    CU_ASSERT_EQUAL(startingCentroids1[4]->vector[1], 4);


    //test : ex3.bin
    CU_ASSERT_EQUAL(startingCentroids2[0]->vector[0], 2053);
    CU_ASSERT_EQUAL(startingCentroids2[0]->vector[1], 981);

    CU_ASSERT_EQUAL(startingCentroids2[1]->vector[0], 2053);
    CU_ASSERT_EQUAL(startingCentroids2[1]->vector[1], 981);

    CU_ASSERT_EQUAL(startingCentroids2[2]->vector[0], 2053);
    CU_ASSERT_EQUAL(startingCentroids2[2]->vector[1], 981);

    CU_ASSERT_EQUAL(startingCentroids2[3]->vector[0], 515);
    CU_ASSERT_EQUAL(startingCentroids2[3]->vector[1], 486);

    CU_ASSERT_EQUAL(startingCentroids2[4]->vector[0], 988);
    CU_ASSERT_EQUAL(startingCentroids2[4]->vector[1], 519);

}


int main() {

    CU_pSuite distanceTestSuite = NULL;
    CU_pSuite distortionTestSuite = NULL;
    CU_pSuite updateCentroidsTestSuite = NULL;
    CU_pSuite assignVectorSuite = NULL;
    CU_pSuite kmeansSuite = NULL;
    CU_pSuite binaryFileSuite = NULL;
    CU_pSuite csvFileSuite = NULL;
    CU_pSuite generateStartingCentroidsSuite = NULL;

    /** initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /** add a suite to the registry */
    distanceTestSuite = CU_add_suite("distance tests", distanceSetup, distanceTeardown);
    distortionTestSuite = CU_add_suite("distortion test", setup, teardown);
    generateStartingCentroidsSuite = CU_add_suite("generateStartingCentroids test", setupGenerateStartingCentroids,
                                                  teardownGenerateStartingCentroids);
    updateCentroidsTestSuite = CU_add_suite("updateCentroids test", setup, teardown);
    assignVectorSuite = CU_add_suite("Assign vector", setup, teardown);
    kmeansSuite = CU_add_suite("Kmeans test", setup, teardown);
    binaryFileSuite = CU_add_suite("binary file loading test", setupBinaryFile, teardownBinaryFile);
    csvFileSuite = CU_add_suite("writing into csv file", setupCreateOutputfile, teardownCreateOutputFile);

    if (distanceTestSuite == NULL || distortionTestSuite == NULL ||
        updateCentroidsTestSuite == NULL || assignVectorSuite == NULL || kmeansSuite == NULL
        || binaryFileSuite == NULL || csvFileSuite == NULL || generateStartingCentroidsSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** add the tests to the suite */
    /** NOTE - ORDER IS IMPORTANT */
    if ((NULL == CU_add_test(distanceTestSuite, "squared manhattan distance", testManhattan)) ||
        (NULL == CU_add_test(distanceTestSuite, "squared euclidean distance", testEuclidean)) ||
        (NULL == CU_add_test(distortionTestSuite, "distortion", testDistortion))
        //TODO : fix tests  (Seb)
        //|| (NULL == CU_add_test(generateStartingCentroidsSuite, "test to generate centroids", testGenerateStartingCentroids))
        ||
        (NULL == CU_add_test(updateCentroidsTestSuite, "updateCentroids", testUpdateCentroids)) ||
        (NULL == CU_add_test(assignVectorSuite, "assign vector normal", testNormalAssignVectorToCentroids)) ||
        (NULL == CU_add_test(assignVectorSuite, "assign vector first", testFirstAssignVectorToCentroids)) ||
        (NULL == CU_add_test(kmeansSuite, "One iteration of Kmeans", testKmeansDimension2)) ||
        //TODO debug test dimension 3
        //(NULL == CU_add_test(kmeansSuite, "Two iterations of Kmeans with dimension 3", testKmeansDimension3)) ||
        (NULL == CU_add_test(binaryFileSuite, "Test of loadingData", testReadBinaryFile))
        // TODO : fix memory leak (Loic)
        /*||
        (NULL == CU_add_test(csvFileSuite, "test of writing into csv", test_createOutputFileDimension2))*/
            ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}