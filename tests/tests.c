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

    kMeansDim3 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim3 == NULL) return -1;
    kMeansDim3->dimension = (int32_t) 3;
    kMeansDim3->points = (point_t *) malloc(3 * sizeof(point_t));
    if (kMeansDim3->points == NULL) return -1;

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

    (kMeansDim3->points)[0].vector  = malloc(3 * sizeof(int64_t));
    if ((kMeansDim3->points)[0].vector == NULL) return -1;
    ((kMeansDim3->points)[0].vector)[0] = (int64_t) - 1;
    ((kMeansDim3->points)[0].vector)[1] = (int64_t) 4;
    ((kMeansDim3->points)[0].vector)[2] = (int64_t) 4;

    (kMeansDim3->points)[1].vector = malloc(3 * sizeof(int64_t));
    if ((kMeansDim3->points)[1].vector== NULL) return -1;
    ((kMeansDim3->points)[1].vector)[0] = (int64_t) - 1;
    ((kMeansDim3->points)[1].vector)[1] = (int64_t) - 2;
    ((kMeansDim3->points)[1].vector)[2] = (int64_t) 9;
    return 0;
}

int32_t teardown(void) {
    free((kMeansDim1->points)[0].vector);
    free((kMeansDim1->points)[1].vector);
    free(kMeansDim1->points);
    free(kMeansDim1);
    free((kMeansDim2->points)[0].vector);
    free((kMeansDim2->points)[1].vector);
    free((kMeansDim2->points)[2].vector);
    free((kMeansDim2->centroids)[0].vector);
    free((kMeansDim2->centroids)[1].vector);
    free(kMeansDim2->points);
    free(kMeansDim2->centroids);
    free(kMeansDim2);
    free((kMeansDim3->points)[0].vector);
    free((kMeansDim3->points)[1].vector);
    free(kMeansDim3->points);
    free(kMeansDim3);
    return 0;
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

void testKmeans(void) {
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


int main() {

    CU_pSuite distanceTestSuite = NULL;
    CU_pSuite distortionTestSuite = NULL;
    CU_pSuite updateCentroidsTestSuite = NULL;
    CU_pSuite assignVectorSuite = NULL;
    CU_pSuite kmeansSuite = NULL;

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

    if (distanceTestSuite == NULL || distortionTestSuite == NULL ||
        updateCentroidsTestSuite == NULL || assignVectorSuite == NULL || kmeansSuite == NULL) {
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
        (NULL == CU_add_test(kmeansSuite, "Kmeans", testKmeans))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}