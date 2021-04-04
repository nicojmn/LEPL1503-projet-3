#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/distance.h"
#include "../headers/point.h"
#include "../headers/kMeans.h"
#include "../src/distance.c"
#include "../src/kMeans.c"
#include "../src/generateStartingCentroids.c"
#include "../headers/binaryFile.h"
#include "../src/binaryFile.c"
#include "../src/createOutputFile.c"


/** Testing with different dimensions */
k_means_t *kMeansDim1 = NULL;
k_means_t *kMeansDim2 = NULL;
k_means_t *kMeansDim3 = NULL;

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


    return 0;

}

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
    return 0;
}

/** Testing input file */
FILE *fileForTest1;
data_t *dataTest1;
FILE *fileForTest2;
data_t *dataTest2;

int32_t setupBinaryFile(void) {
    fileForTest1 = fopen("input_binary/ex1.bin", "r");
    if (fileForTest1 == NULL) return -1;

    dataTest1 = (data_t *) malloc(sizeof(data_t));
    if (dataTest1 == NULL) return -1;

    fileForTest2 = fopen("input_binary/ex2.bin", "r");
    if (fileForTest2 == NULL) return -1;

    dataTest2 = (data_t *) malloc(sizeof(data_t));
    if (dataTest2 == NULL) return -1;
    return 0;
}

int32_t teardownBinaryFile(void) {
    if (0 != fclose(fileForTest1)) return -1;
    for (uint64_t i = 0; i < dataTest1->size; i++) {
        free((dataTest1->vectors)[i]);
    }
    free(dataTest1->vectors);
    free(dataTest1);

    if (0 != fclose(fileForTest2)) return -1;
    for (uint64_t i = 0; i < dataTest2->size; i++) {
        free((dataTest2->vectors)[i]);
    }
    free(dataTest2->vectors);
    free(dataTest2);
    return 0;
}

void testReadBinaryFile(void) {

    loadData(fileForTest1, dataTest1);
    CU_ASSERT_EQUAL(dataTest1->dimension, 2);
    CU_ASSERT_EQUAL(dataTest1->size, 7);
    CU_ASSERT_EQUAL((dataTest1->vectors)[0][0], 1);
    CU_ASSERT_EQUAL((dataTest1->vectors)[0][1], 1);
    CU_ASSERT_EQUAL((dataTest1->vectors)[3][0], 5);
    CU_ASSERT_EQUAL((dataTest1->vectors)[3][1], 7);
    CU_ASSERT_EQUAL((dataTest1->vectors)[6][0], 4);
    CU_ASSERT_EQUAL((dataTest1->vectors)[6][1], 5);

    loadData(fileForTest2, dataTest2);
    CU_ASSERT_EQUAL(dataTest2->dimension, 2);
    CU_ASSERT_EQUAL(dataTest2->size, 13);
    CU_ASSERT_EQUAL((dataTest2->vectors)[0][0], 1);
    CU_ASSERT_EQUAL((dataTest2->vectors)[0][1], 1);
    CU_ASSERT_EQUAL((dataTest2->vectors)[12][0], 2);
    CU_ASSERT_EQUAL((dataTest2->vectors)[12][1], 1);
}

/** We've used the corresponding python function to get the corrects values */
void testManhattan(void) {
    CU_ASSERT_EQUAL(squared_manhattan_distance(&kMeansDim1->points[0], &kMeansDim1->points[1],
                                               kMeansDim1->dimension), 1);
    CU_ASSERT_EQUAL(squared_manhattan_distance(&kMeansDim2->points[0], &kMeansDim2->points[1],
                                               kMeansDim2->dimension), 16);
    CU_ASSERT_EQUAL(squared_manhattan_distance(&kMeansDim3->points[0], &kMeansDim3->points[1],
                                               kMeansDim3->dimension), 121);
}

/** We've used the corresponding python function to get the corrects values */
void testEuclidean(void) {
    CU_ASSERT_EQUAL(squared_euclidean_distance(&kMeansDim1->points[0], &kMeansDim1->points[1],
                                               kMeansDim1->dimension), 1);
    CU_ASSERT_EQUAL(squared_euclidean_distance(&kMeansDim2->points[0], &kMeansDim2->points[1],
                                               kMeansDim2->dimension), 8);
    CU_ASSERT_EQUAL(squared_euclidean_distance(&kMeansDim3->points[0], &kMeansDim3->points[1],
                                               kMeansDim3->dimension), 61);
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
    squared_distance_func_t generic_func = squared_euclidean_distance;
    FILE *outputFile = NULL;
    outputFile = fopen("test.csv", "a+");
    k_means_t *startingCentroids = (k_means_t *) malloc(sizeof(point_t));

    startingCentroids->centroids = (point_t *) malloc(sizeof(point_t) * 2);
    startingCentroids->centroids[0].vector = malloc(sizeof(int64_t) * 3);

    startingCentroids->centroids[0].vector[0] = (int64_t) -2;
    startingCentroids->centroids[0].vector[1] = (int64_t) 4;
    startingCentroids->centroids[0].vector[2] = (int64_t) 3;

    startingCentroids->centroids[1].vector = malloc(sizeof(point_t) * 3);

    startingCentroids->centroids[1].vector[0] = (int64_t) 6;
    startingCentroids->centroids[1].vector[1] = (int64_t) 2;
    startingCentroids->centroids[1].vector[2] = (int64_t) 1;

    writeOneKmeans(kMeansDim3, false, outputFile, startingCentroids->centroids,
                   (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);

}

void test_createOutputFileDimension2(void) {
    squared_distance_func_t generic_func = squared_manhattan_distance;
    FILE *outputFile = NULL;
    outputFile = fopen("createOutputFile2.csv", "a+");
    k_means_t *startingCentroids = (k_means_t *) malloc(sizeof(point_t));
    k_means(kMeansDim2, (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);

    startingCentroids->centroids = (point_t *) malloc(sizeof(point_t) * 2);
    startingCentroids->centroids[0].vector = malloc(sizeof(int64_t) * 2);

    startingCentroids->centroids[0].vector[0] = (int64_t) 1;
    startingCentroids->centroids[0].vector[1] = (int64_t) 1;

    startingCentroids->centroids[1].vector = malloc(sizeof(point_t) * 2);

    startingCentroids->centroids[1].vector[0] = (int64_t) 2;
    startingCentroids->centroids[1].vector[1] = (int64_t) 2;

    writeOneKmeans(kMeansDim2, false, outputFile, startingCentroids->centroids,
                   (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);
}


void testGenerateStartingCentroids(void) {

    /*
    tentative d initialisation de centroid
    (kMeansDim2->points)[0].nearestCentroidID = ?;
    startingCentroidsID[?][?].vector = vectors[?];

    CU_ASSERT_EQUAL(generateSetOfStartingCentroids(argument1, argument2 , 4, 4, 1), returned)
    - argument1 c'est le centroide du point qui va être initialisé
    - argument2 c'est le vecteur associé
    - returned c'est j'imagine genre une mini liste du genre [0 1 2 3] dans ce cas ci

     -> reste à comprendre comment initialisé tout ça  (voir tentative au dessus)
     -> est ce que j'ai l'air de bégayé avec les tests ? oui totalement
     */

}


int main() {

    CU_pSuite distanceTestSuite = NULL;
    CU_pSuite distortionTestSuite = NULL;
    CU_pSuite updateCentroidsTestSuite = NULL;
    CU_pSuite assignVectorSuite = NULL;
    CU_pSuite kmeansSuite = NULL;
    CU_pSuite binaryFileSuite = NULL;
    CU_pSuite csvFileSuite = NULL;

    /** initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /** add a suite to the registry */
    distanceTestSuite = CU_add_suite("distance tests", setup, teardown);
    distortionTestSuite = CU_add_suite("distortion test", setup, teardown);
    updateCentroidsTestSuite = CU_add_suite("updateCentroids test", setup, teardown);
    assignVectorSuite = CU_add_suite("Assign vector", setup, teardown);
    kmeansSuite = CU_add_suite("Kmeans test", setup, teardown);
    binaryFileSuite = CU_add_suite("binary file loading test", setupBinaryFile, teardownBinaryFile);
    csvFileSuite = CU_add_suite("writing into csv file", setupCreateOutputfile, teardownCreateOutputFile);

    if (distanceTestSuite == NULL || distortionTestSuite == NULL ||
        updateCentroidsTestSuite == NULL || assignVectorSuite == NULL || kmeansSuite == NULL
        || binaryFileSuite == NULL || csvFileSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** add the tests to the suite */
    /** NOTE - ORDER IS IMPORTANT */
    if ((NULL == CU_add_test(distanceTestSuite, "squared manhattan distance", testManhattan)) ||
        (NULL == CU_add_test(distanceTestSuite, "squared euclidean distance", testEuclidean)) ||
        (NULL == CU_add_test(distortionTestSuite, "distortion", testDistortion)) ||
        (NULL == CU_add_test(updateCentroidsTestSuite, "updateCentroids", testUpdateCentroids)) ||
        (NULL == CU_add_test(assignVectorSuite, "assign vector normal", testNormalAssignVectorToCentroids)) ||
        (NULL == CU_add_test(assignVectorSuite, "assign vector first", testFirstAssignVectorToCentroids)) ||
        (NULL == CU_add_test(kmeansSuite, "One iteration of Kmeans", testKmeansDimension2)) ||
        NULL == CU_add_test(kmeansSuite, "Two iterations of Kmeans with dimension 3", testKmeansDimension3) ||
        NULL == CU_add_test(binaryFileSuite, "Test of loadingData", testReadBinaryFile) ||
        /*NULL == CU_add_test(csvFileSuite,"test of writing into csv",test_createOutputFileDimension3)||*/
        NULL == CU_add_test(csvFileSuite, "test of writing into csv", test_createOutputFileDimension2)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}