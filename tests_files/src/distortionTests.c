#include "../headers/distortionTests.h"

kMeans_t *distortionKMeansDim2 = NULL;

int32_t distortionSetup(void) {

    distortionKMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (distortionKMeansDim2 == NULL) return -1;
    distortionKMeansDim2->dimension = (int32_t) 2;
    distortionKMeansDim2->points = (point_t *) malloc(5 * sizeof(point_t));
    distortionKMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (distortionKMeansDim2->points == NULL) return -1;
    distortionKMeansDim2->size = 3;
    distortionKMeansDim2->k = 2;
    distortionKMeansDim2->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (distortionKMeansDim2->clustersSize == NULL) return -1;

    (distortionKMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((distortionKMeansDim2->points)[0].vector == NULL) return -1;
    ((distortionKMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((distortionKMeansDim2->points)[0].vector)[1] = (int64_t) 2;
    (distortionKMeansDim2->points)[0].nearestCentroidID = 0;

    (distortionKMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((distortionKMeansDim2->points)[1].vector == NULL) return -1;
    ((distortionKMeansDim2->points)[1].vector)[0] = (int64_t) -1;
    ((distortionKMeansDim2->points)[1].vector)[1] = (int64_t) 4;
    (distortionKMeansDim2->points)[1].nearestCentroidID = 0;

    (distortionKMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((distortionKMeansDim2->points)[2].vector == NULL) return -1;
    ((distortionKMeansDim2->points)[2].vector)[0] = (int64_t) -4;
    ((distortionKMeansDim2->points)[2].vector)[1] = (int64_t) 10;
    (distortionKMeansDim2->points)[2].nearestCentroidID = 1;

    (distortionKMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((distortionKMeansDim2->centroids)[0].vector == NULL) return -1;
    ((distortionKMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((distortionKMeansDim2->centroids)[0].vector)[1] = (int64_t) 2;

    (distortionKMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((distortionKMeansDim2->centroids)[1].vector == NULL) return -1;
    ((distortionKMeansDim2->centroids)[1].vector)[0] = (int64_t) -3;
    ((distortionKMeansDim2->centroids)[1].vector)[1] = (int64_t) 9;
    return 0;
}

int32_t distortionTeardown(void) {

    free((distortionKMeansDim2->points)[0].vector);
    free((distortionKMeansDim2->points)[1].vector);
    free((distortionKMeansDim2->points)[2].vector);
    free((distortionKMeansDim2->centroids)[0].vector);
    free((distortionKMeansDim2->centroids)[1].vector);
    free(distortionKMeansDim2->points);
    free(distortionKMeansDim2->centroids);
    free(distortionKMeansDim2->clustersSize);
    free(distortionKMeansDim2);
    return 0;
}


/** We've used the corresponding python function to get the correct value */
void testDistortion(void) {
    squared_distance_func_t generic_func = squared_euclidean_distance;
    CU_ASSERT_EQUAL(distortion(distortionKMeansDim2,
                               (squared_distance_func_t (*)(const point_t *, const point_t *, uint32_t)) generic_func),
                    10);
    generic_func = squared_manhattan_distance;
    CU_ASSERT_EQUAL(distortion(distortionKMeansDim2,
                               (squared_distance_func_t (*)(const point_t *, const point_t *, uint32_t)) generic_func),
                    20);
}