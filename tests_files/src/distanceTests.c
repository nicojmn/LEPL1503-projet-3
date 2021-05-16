#include "../headers/distanceTests.h"

kMeans_t *distanceKMeansDim1 = NULL;
kMeans_t *distanceKMeansDim2 = NULL;
kMeans_t *distanceKMeansDim3 = NULL;

int32_t distanceSetup(void) {
    /**
     * Creation of a simulation:
     *    - in 1 dimension
     *    - 2 points: [(1), (2)]
     */
    distanceKMeansDim1 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (distanceKMeansDim1 == NULL) return -1;
    distanceKMeansDim1->dimension = (int32_t) 1;
    distanceKMeansDim1->points = (point_t *) malloc(2 * sizeof(point_t));
    if (distanceKMeansDim1->points == NULL) return -1;

    (distanceKMeansDim1->points)[0].vector = malloc(1 * sizeof(int64_t));
    if ((distanceKMeansDim1->points)[0].vector == NULL) return -1;
    ((distanceKMeansDim1->points)[0].vector)[0] = (int64_t) 1;

    (distanceKMeansDim1->points)[1].vector = malloc(1 * sizeof(int64_t));
    if ((distanceKMeansDim1->points)[1].vector == NULL) return -1;
    ((distanceKMeansDim1->points)[1].vector)[0] = (int64_t) 2;

    /**
     * Creation of a simulation:
     *    - in 2 dimensions
     *    - 2 points: [(1, 2), (-1, 4)]
     */
    distanceKMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (distanceKMeansDim2 == NULL) return -1;
    distanceKMeansDim2->dimension = (int32_t) 2;
    distanceKMeansDim2->points = (point_t *) malloc(2 * sizeof(point_t));
    if (distanceKMeansDim2->points == NULL) return -1;

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

    /**
     * Creation of a simulation:
     *    - in 3 dimensions
     *    - 2 points: [(-1, 4, 4), (-1, -2, 9)]
     */
    distanceKMeansDim3 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (distanceKMeansDim3 == NULL) return -1;
    distanceKMeansDim3->dimension = (int32_t) 3;
    distanceKMeansDim3->points = (point_t *) malloc(2 * sizeof(point_t));
    if (distanceKMeansDim3->points == NULL) return -1;

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

    return 0;
}

int32_t distanceTeardown(void) {
    free((distanceKMeansDim1->points)[0].vector);
    free((distanceKMeansDim1->points)[1].vector);
    free(distanceKMeansDim1->points);
    free(distanceKMeansDim1);

    free((distanceKMeansDim2->points)[0].vector);
    free((distanceKMeansDim2->points)[1].vector);
    free(distanceKMeansDim2->points);
    free(distanceKMeansDim2);

    free((distanceKMeansDim3->points)[0].vector);
    free((distanceKMeansDim3->points)[1].vector);
    free(distanceKMeansDim3->points);
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