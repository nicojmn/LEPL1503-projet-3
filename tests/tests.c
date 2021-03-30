#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/distance.h"
#include "../src/distance.c"
#include "../headers/point.h"
#include "../headers/kMeans.h"


// Testing with different dimensions
k_means_t *kMeansDim1 = NULL;
k_means_t *kMeansDim2 = NULL;
k_means_t *kMeansDim3 = NULL;

int distanceSetup(void) {
    kMeansDim1 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim1 == NULL) return -1;
    kMeansDim1->dimension = (int32_t) 1;
    kMeansDim1->points = (point_t *) malloc(1 * sizeof(point_t));
    if (kMeansDim1->points == NULL) return -1;

    kMeansDim2 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim2 == NULL) return -1;
    kMeansDim2->dimension = (int32_t) 2;
    kMeansDim2->points = (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim2->points == NULL) return -1;

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

    (kMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((kMeansDim2->points)[1].vector == NULL) return -1;
    ((kMeansDim2->points)[1].vector)[0] = (int64_t) - 1;
    ((kMeansDim2->points)[1].vector)[1] = (int64_t) 4;

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

int distanceTeardown(void) {
    free((kMeansDim1->points)[0].vector); free((kMeansDim1->points)[1].vector);
    free(kMeansDim1->points); free(kMeansDim1);
    free((kMeansDim2->points)[0].vector); free((kMeansDim2->points)[1].vector);
    free(kMeansDim2->points); free(kMeansDim2);
    free((kMeansDim3->points)[0].vector); free((kMeansDim3->points)[1].vector);
    free(kMeansDim3->points); free(kMeansDim3);
    return 0;
}

// We've used the python functions to get the aiming behaviour
void testManhattan(void) {
    CU_ASSERT_EQUAL(squared_manhattan_distance(&kMeansDim1->points[0], &kMeansDim1->points[1],
                                               kMeansDim1->dimension), 1);
    CU_ASSERT_EQUAL(squared_manhattan_distance(&kMeansDim2->points[0], &kMeansDim2->points[1],
                                               kMeansDim2->dimension), 16);
    CU_ASSERT_EQUAL(squared_manhattan_distance(&kMeansDim3->points[0], &kMeansDim3->points[1],
                                               kMeansDim3->dimension), 121);
}

void testEuclidean(void) {
    CU_ASSERT_EQUAL(squared_euclidean_distance(&kMeansDim1->points[0], &kMeansDim1->points[1],
                                               kMeansDim1->dimension), 1);
    CU_ASSERT_EQUAL(squared_euclidean_distance(&kMeansDim2->points[0], &kMeansDim2->points[1],
                                               kMeansDim2->dimension), 8);
    CU_ASSERT_EQUAL(squared_euclidean_distance(&kMeansDim3->points[0], &kMeansDim3->points[1],
                                               kMeansDim3->dimension), 61);
}

int main() {

    CU_pSuite distanceSuite = NULL;

    /** initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /** add a suite to the registry */
    distanceSuite = CU_add_suite("distance tests", distanceSetup, distanceTeardown);
    if (NULL == distanceSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** add the tests to the suite */
    /** NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if ((NULL == CU_add_test(distanceSuite, "squared manhattan distance", testManhattan)) ||
        (NULL == CU_add_test(distanceSuite, "squared euclidean distance", testEuclidean))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}