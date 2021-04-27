#include <CUnit/CUnit.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>


#include "../headers/updateCentroidsTests.h"
kMeans_t *updateKMeansDim2 = NULL;
/** We've used the corresponding python function to get the correct value */
int32_t updateCentroidsSetup(void) {
    updateKMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (updateKMeansDim2 == NULL) return -1;
    updateKMeansDim2->dimension = (int32_t) 2;
    updateKMeansDim2->points = (point_t *) malloc(5 * sizeof(point_t));
    updateKMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (updateKMeansDim2->points == NULL) return -1;
    updateKMeansDim2->size = 3;
    updateKMeansDim2->k = 2;
    updateKMeansDim2->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (updateKMeansDim2->clustersSize == NULL) return -1;

    (updateKMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((updateKMeansDim2->points)[0].vector == NULL) return -1;
    ((updateKMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((updateKMeansDim2->points)[0].vector)[1] = (int64_t) 2;
    (updateKMeansDim2->points)[0].nearestCentroidID = 0;


    (updateKMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((updateKMeansDim2->points)[1].vector == NULL) return -1;
    ((updateKMeansDim2->points)[1].vector)[0] = (int64_t) -1;
    ((updateKMeansDim2->points)[1].vector)[1] = (int64_t) 4;
    (updateKMeansDim2->points)[1].nearestCentroidID = 0;

    (updateKMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((updateKMeansDim2->points)[2].vector == NULL) return -1;
    ((updateKMeansDim2->points)[2].vector)[0] = (int64_t) -4;
    ((updateKMeansDim2->points)[2].vector)[1] = (int64_t) 10;
    (updateKMeansDim2->points)[2].nearestCentroidID = 1;

    (updateKMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((updateKMeansDim2->centroids)[0].vector == NULL) return -1;
    ((updateKMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((updateKMeansDim2->centroids)[0].vector)[1] = (int64_t) 2;

    (updateKMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((updateKMeansDim2->centroids)[1].vector == NULL) return -1;
    ((updateKMeansDim2->centroids)[1].vector)[0] = (int64_t) -3;
    ((updateKMeansDim2->centroids)[1].vector)[1] = (int64_t) 9;

    return 0;
}

int32_t updateCentroidsTeardown(void) {
    free((updateKMeansDim2->points)[0].vector);
    free((updateKMeansDim2->points)[1].vector);
    free((updateKMeansDim2->points)[2].vector);
    free((updateKMeansDim2->centroids)[0].vector);
    free((updateKMeansDim2->centroids)[1].vector);
    free(updateKMeansDim2->points);
    free(updateKMeansDim2->centroids);
    free(updateKMeansDim2->clustersSize);
    free(updateKMeansDim2);
    return 0;
}

/** We've used the corresponding python function to get the correct value */
void testUpdateCentroids(void) {
    updateCentroids(updateKMeansDim2);
    CU_ASSERT_EQUAL((updateKMeansDim2->centroids)[0].vector[0], (int64_t) 0);
    CU_ASSERT_EQUAL((updateKMeansDim2->centroids)[0].vector[1], (int64_t) 3);
    CU_ASSERT_EQUAL((updateKMeansDim2->centroids)[1].vector[0], (int64_t) -4);
    CU_ASSERT_EQUAL((updateKMeansDim2->centroids)[1].vector[1], (int64_t) 10);
}
