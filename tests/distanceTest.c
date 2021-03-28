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

point_t *a = NULL;
point_t *b = NULL;
point_t *c = NULL;
point_t *d = NULL;
point_t *e = NULL;
point_t *f = NULL;

int setup(void) {
    kMeansDim1 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim1 == NULL) return -1;
    kMeansDim1->dimension = (uint32_t) 1;
    kMeansDim1->points = (point_t **) (point_t *) malloc(1 * sizeof(point_t));
    if (kMeansDim1->points == NULL) return -1;

    kMeansDim2 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim2 == NULL) return -1;
    kMeansDim2->dimension = (uint32_t) 2;
    kMeansDim2->points = (point_t **) (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim2->points == NULL) return -1;

    kMeansDim3 = (k_means_t *) malloc(sizeof(k_means_t));
    if (kMeansDim3 == NULL) return -1;
    kMeansDim3->dimension = (uint32_t) 3;
    kMeansDim3->points = (point_t **) (point_t *) malloc(3 * sizeof(point_t));
    if (kMeansDim3->points == NULL) return -1;

    a = (point_t *) malloc(sizeof(point_t));
    if (a == NULL) return -1;
    a->vector = malloc(1 * sizeof(int64_t));
    if (a->vector == NULL) return -1;
    (a->vector)[0] = (int64_t) 1;
    (kMeansDim1->points)[0] = a;

    b = (point_t *) malloc(sizeof(point_t));
    if (b == NULL) return -1;
    b->vector = malloc(1 * sizeof(int64_t));
    if (b->vector == NULL) return -1;
    (b->vector)[0] = (int64_t) 2;
    (kMeansDim1->points)[1] = b;

    c = (point_t *) malloc(sizeof(point_t));
    if (c == NULL) return -1;
    c->vector = malloc(2 * sizeof(int64_t));
    if (c->vector == NULL) return -1;
    (c->vector)[0] = (int64_t) 1;
    (c->vector)[1] = (int64_t) 2;
    (kMeansDim2->points)[0] = c;

    d = (point_t *) malloc(sizeof(point_t));
    if (d == NULL) return -1;
    d->vector = malloc(2 * sizeof(int64_t));
    if (d->vector == NULL) return -1;
    (d->vector)[0] = (int64_t) - 1;
    (d->vector)[1] = (int64_t) 4;
    (kMeansDim2->points)[1] = d;

    e = (point_t *) malloc(sizeof(point_t));
    if (e == NULL) return -1;
    e->vector = malloc(3 * sizeof(int64_t));
    if (e->vector == NULL) return -1;
    (e->vector)[0] = (int64_t) - 1;
    (e->vector)[1] = (int64_t) 4;
    (e->vector)[2] = (int64_t) 4;
    (kMeansDim3->points)[0] = e;

    f = (point_t *) malloc(sizeof(point_t));
    if (f == NULL) return -1;
    f->vector = malloc(3 * sizeof(int64_t));
    if (f->vector == NULL) return -1;
    (f->vector)[0] = (int64_t) - 1;
    (f->vector)[1] = (int64_t) - 2;
    (f->vector)[2] = (int64_t) 9;
    (kMeansDim3->points)[1] = f;
    return 0;
}

int teardown(void) {
    free(a->vector);
    free(a);
    free(b->vector);
    free(b);
    free(kMeansDim1->points);
    free(kMeansDim1);
    free(c->vector);
    free(c);
    free(d->vector);
    free(d);
    free(kMeansDim2->points);
    free(kMeansDim2);
    free(e->vector);
    free(e);
    free(f->vector);
    free(f);
    free(kMeansDim3->points);
    free(kMeansDim3);
    return 0;
}

// We've used the python functions to get the aiming behaviour
void testManhattan(void) {
    CU_ASSERT_EQUAL(squared_manhattan_distance(kMeansDim1->points[0], kMeansDim1->points[1],
                                               kMeansDim1->dimension), 1);
    CU_ASSERT_EQUAL(squared_manhattan_distance(kMeansDim2->points[0], kMeansDim2->points[1],
                                               kMeansDim2->dimension), 16);
    CU_ASSERT_EQUAL(squared_manhattan_distance(kMeansDim3->points[0], kMeansDim3->points[1],
                                               kMeansDim3->dimension), 121);
}

void testEuclidean(void) {
    CU_ASSERT_EQUAL(squared_euclidean_distance(kMeansDim1->points[0], kMeansDim1->points[1],
                                               kMeansDim1->dimension), 1);
    CU_ASSERT_EQUAL(squared_euclidean_distance(kMeansDim2->points[0], kMeansDim2->points[1],
                                               kMeansDim2->dimension), 8);
    CU_ASSERT_EQUAL(squared_euclidean_distance(kMeansDim3->points[0], kMeansDim3->points[1],
                                               kMeansDim3->dimension), 61);
}

int main() {

    CU_pSuite pSuite = NULL;

    /** initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /** add a suite to the registry */
    pSuite = CU_add_suite("Suite_1", setup, teardown);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** add the tests to the suite */
    /** NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    if ((NULL == CU_add_test(pSuite, "test of squared_manhattan_distance()", testManhattan)) ||
        (NULL == CU_add_test(pSuite, "test of squared_euclidean_distance()", testEuclidean))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}


