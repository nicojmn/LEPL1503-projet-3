#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/updateCentroidsTests.h"


kMeans_t *updateCentroidsKMeansDim2 = NULL;

int32_t updateCentroidsSetup(void) {

    /**
     * Creation of a simulation:
     *    - in 2 dimensions
     *    - 3 points: [(1, 2), (-1, 4), (-4, 10)]
     *    - 2 centroids: [(1, 2), (-3, 9)]
     */
    updateCentroidsKMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (updateCentroidsKMeansDim2 == NULL) return -1;
    updateCentroidsKMeansDim2->dimension = (int32_t) 2;
    updateCentroidsKMeansDim2->points = (point_t *) malloc(3 * sizeof(point_t));
    if (updateCentroidsKMeansDim2->points == NULL) return -1;
    updateCentroidsKMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (updateCentroidsKMeansDim2->centroids == NULL) return -1;
    updateCentroidsKMeansDim2->size = 3;
    updateCentroidsKMeansDim2->k = 2;
    updateCentroidsKMeansDim2->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (updateCentroidsKMeansDim2->clustersSize == NULL) return -1;

    (updateCentroidsKMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((updateCentroidsKMeansDim2->points)[0].vector == NULL) return -1;
    ((updateCentroidsKMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((updateCentroidsKMeansDim2->points)[0].vector)[1] = (int64_t) 2;
    (updateCentroidsKMeansDim2->points)[0].nearestCentroidID = 0;


    (updateCentroidsKMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((updateCentroidsKMeansDim2->points)[1].vector == NULL) return -1;
    ((updateCentroidsKMeansDim2->points)[1].vector)[0] = (int64_t) -1;
    ((updateCentroidsKMeansDim2->points)[1].vector)[1] = (int64_t) 4;
    (updateCentroidsKMeansDim2->points)[1].nearestCentroidID = 0;

    (updateCentroidsKMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((updateCentroidsKMeansDim2->points)[2].vector == NULL) return -1;
    ((updateCentroidsKMeansDim2->points)[2].vector)[0] = (int64_t) -4;
    ((updateCentroidsKMeansDim2->points)[2].vector)[1] = (int64_t) 10;
    (updateCentroidsKMeansDim2->points)[2].nearestCentroidID = 1;

    (updateCentroidsKMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((updateCentroidsKMeansDim2->centroids)[0].vector == NULL) return -1;
    ((updateCentroidsKMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((updateCentroidsKMeansDim2->centroids)[0].vector)[1] = (int64_t) 2;

    (updateCentroidsKMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((updateCentroidsKMeansDim2->centroids)[1].vector == NULL) return -1;
    ((updateCentroidsKMeansDim2->centroids)[1].vector)[0] = (int64_t) -3;
    ((updateCentroidsKMeansDim2->centroids)[1].vector)[1] = (int64_t) 9;

    return 0;
}

int32_t updateCentroidsTeardown(void) {
    free((updateCentroidsKMeansDim2->points)[0].vector);
    free((updateCentroidsKMeansDim2->points)[1].vector);
    free((updateCentroidsKMeansDim2->points)[2].vector);
    free((updateCentroidsKMeansDim2->centroids)[0].vector);
    free((updateCentroidsKMeansDim2->centroids)[1].vector);
    free(updateCentroidsKMeansDim2->points);
    free(updateCentroidsKMeansDim2->centroids);
    free(updateCentroidsKMeansDim2->clustersSize);
    free(updateCentroidsKMeansDim2);
    return 0;
}

/** We've used the corresponding python function to get the correct value */
void testUpdateCentroids(void) {
    updateCentroids(updateCentroidsKMeansDim2);
    CU_ASSERT_EQUAL((updateCentroidsKMeansDim2->centroids)[0].vector[0], (int64_t) 0);
    CU_ASSERT_EQUAL((updateCentroidsKMeansDim2->centroids)[0].vector[1], (int64_t) 3);
    CU_ASSERT_EQUAL((updateCentroidsKMeansDim2->centroids)[1].vector[0], (int64_t) -4);
    CU_ASSERT_EQUAL((updateCentroidsKMeansDim2->centroids)[1].vector[1], (int64_t) 10);
}
