#include "../headers/writeOutputFileTests.h"

point_t **writeOutputFileCentroids1;

FILE *writeOutputFile = NULL;

kMeans_t *outputKMeansDim2 = NULL;


int32_t setupCreateOutputFile(void) {

    /**
     * Creation of a simulation:
     *    - in 2 dimensions
     *    - 7 points: [(1, 1), (2, 2), (3, 4), (5, 7), (3, 5), (5, 5), (4, 5)]
     *    - 2 centroids: [(1, 1), (2, 2)]
     */
    outputKMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (outputKMeansDim2 == NULL) return -1;
    outputKMeansDim2->dimension = (int32_t) 2;
    outputKMeansDim2->points = (point_t *) malloc(7 * sizeof(point_t));
    if (outputKMeansDim2->points == NULL) return -1;
    outputKMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (outputKMeansDim2->centroids == NULL) return -1;
    outputKMeansDim2->size = 7;
    outputKMeansDim2->k = 2;
    outputKMeansDim2->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (outputKMeansDim2->clustersSize == NULL) return -1;

    (outputKMeansDim2->points)[0].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim2->points)[0].vector == NULL) return -1;
    ((outputKMeansDim2->points)[0].vector)[0] = (int64_t) 1;
    ((outputKMeansDim2->points)[0].vector)[1] = (int64_t) 1;
    (outputKMeansDim2->points)[0].nearestCentroidID = 0;

    (outputKMeansDim2->points)[1].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim2->points)[1].vector == NULL) return -1;
    ((outputKMeansDim2->points)[1].vector)[0] = (int64_t) 2;
    ((outputKMeansDim2->points)[1].vector)[1] = (int64_t) 2;
    (outputKMeansDim2->points)[1].nearestCentroidID = 1;

    (outputKMeansDim2->points)[2].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim2->points)[2].vector == NULL) return -1;
    ((outputKMeansDim2->points)[2].vector)[0] = (int64_t) 3;
    ((outputKMeansDim2->points)[2].vector)[1] = (int64_t) 4;
    (outputKMeansDim2->points)[2].nearestCentroidID = -1;

    (outputKMeansDim2->points)[3].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim2->points)[3].vector == NULL) return -1;
    ((outputKMeansDim2->points)[3].vector)[0] = (int64_t) 5;
    ((outputKMeansDim2->points)[3].vector)[1] = (int64_t) 7;
    (outputKMeansDim2->points)[3].nearestCentroidID = -1;


    (outputKMeansDim2->points)[4].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim2->points)[4].vector == NULL) return -1;
    ((outputKMeansDim2->points)[4].vector)[0] = (int64_t) 3;
    ((outputKMeansDim2->points)[4].vector)[1] = (int64_t) 5;
    (outputKMeansDim2->points)[4].nearestCentroidID = -1;

    (outputKMeansDim2->points)[5].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim2->points)[5].vector == NULL) return -1;
    ((outputKMeansDim2->points)[5].vector)[0] = (int64_t) 5;
    ((outputKMeansDim2->points)[5].vector)[1] = (int64_t) 5;
    (outputKMeansDim2->points)[5].nearestCentroidID = -1;

    (outputKMeansDim2->points)[6].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim2->points)[6].vector == NULL) return -1;
    ((outputKMeansDim2->points)[6].vector)[0] = (int64_t) 4;
    ((outputKMeansDim2->points)[6].vector)[1] = (int64_t) 5;
    (outputKMeansDim2->points)[6].nearestCentroidID = -1;

    (outputKMeansDim2->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim2->centroids)[0].vector == NULL) return -1;
    ((outputKMeansDim2->centroids)[0].vector)[0] = (int64_t) 1;
    ((outputKMeansDim2->centroids)[0].vector)[1] = (int64_t) 1;

    (outputKMeansDim2->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim2->centroids)[1].vector == NULL) return -1;
    ((outputKMeansDim2->centroids)[1].vector)[0] = (int64_t) 2;
    ((outputKMeansDim2->centroids)[1].vector)[1] = (int64_t) 2;

    /** We record the starting centroids */
    writeOutputFileCentroids1 = (point_t **) malloc(sizeof(point_t *));
    if (writeOutputFileCentroids1 == NULL) return -1;
    writeOutputFileCentroids1[0] = malloc(sizeof(point_t) * 2);
    if (writeOutputFileCentroids1 == NULL) return -1;

    writeOutputFileCentroids1[0][0].vector = malloc(sizeof(int64_t) * 3);
    if (writeOutputFileCentroids1[0][0].vector == NULL) return -1;
    writeOutputFileCentroids1[0][0].vector[0] = (int64_t) -2;
    writeOutputFileCentroids1[0][0].vector[1] = (int64_t) 4;
    writeOutputFileCentroids1[0][0].vector[2] = (int64_t) 3;

    writeOutputFileCentroids1[0][1].vector = malloc(sizeof(point_t) * 3);
    if (writeOutputFileCentroids1[0][1].vector == NULL) return -1;
    writeOutputFileCentroids1[0][1].vector[0] = (int64_t) 6;
    writeOutputFileCentroids1[0][1].vector[1] = (int64_t) 2;
    writeOutputFileCentroids1[0][1].vector[2] = (int64_t) 1;

    writeOutputFile = fopen("tests_files/output_csv/ex1.csv", "w");
    return 0;
}


int32_t teardownCreateOutputFile(void) {
    int64_t numberOfPoints = 7;
    int32_t k = 2;
    for (int i = 0; i < numberOfPoints; i++) {
        free(outputKMeansDim2->points[i].vector);
    }
    for (int i = 0; i < k; i++) {
        free(outputKMeansDim2->centroids[i].vector);
    }
    for (int i = 0; i < k; i++) {
        free(writeOutputFileCentroids1[0][i].vector);
    }
    free(writeOutputFileCentroids1[0]);

    free(outputKMeansDim2->points);
    free(outputKMeansDim2->centroids);
    free(outputKMeansDim2->clustersSize);
    free(outputKMeansDim2);

    fclose(writeOutputFile);
    writeOutputFile = NULL;

    free(writeOutputFileCentroids1);
    return 0;
}

/**
 * We only check here if everything looks good
 * For better assessment, we've used compare_solutions.py
 */
void test_createOutputFileDimension2(void) {
    squared_distance_func_t generic_func = squared_manhattan_distance;
    runKMeans(outputKMeansDim2, (squared_distance_func_t (*)(const point_t *, const point_t *, uint32_t)) generic_func);
    writeHeadline(false, writeOutputFile);
    point_t **clusters = generateClusters(outputKMeansDim2, false);
    uint64_t distortionValue = distortion(outputKMeansDim2,
                                          (squared_distance_func_t (*)(const point_t *, const point_t *, uint32_t))
                                                  generic_func);
    CU_ASSERT_EQUAL(writeOneKMeans(outputKMeansDim2, false, writeOutputFile, writeOutputFileCentroids1[0],
                                   clusters, distortionValue), 0);
}