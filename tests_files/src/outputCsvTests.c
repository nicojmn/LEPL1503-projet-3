#include "../headers/outputCsvTests.h"

point_t **outputStartingCentroids1;
point_t **outputStartingCentroids2;

FILE *outputFile;

kMeans_t *outputKMeansDim2 = NULL;
kMeans_t *outputKMeansDim3 = NULL;

int32_t setupCreateOutputFile(void) {

    outputKMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (outputKMeansDim2 == NULL) return -1;
    outputKMeansDim2->dimension = (int32_t) 2;
    outputKMeansDim2->points = (point_t *) malloc(7 * sizeof(point_t));
    outputKMeansDim2->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (outputKMeansDim2->points == NULL) return -1;
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

    outputKMeansDim3 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (outputKMeansDim3 == NULL) return -1;
    outputKMeansDim3->dimension = (int32_t) 3;
    outputKMeansDim3->points = (point_t *) malloc(6 * sizeof(point_t));
    outputKMeansDim3->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (outputKMeansDim3->points == NULL) return -1;
    outputKMeansDim3->size = 6;
    outputKMeansDim3->k = 2;
    outputKMeansDim3->clustersSize = (uint64_t *) malloc(2 * sizeof(uint64_t *));
    if (outputKMeansDim3->clustersSize == NULL) return -1;

    (outputKMeansDim3->points)[0].vector = malloc(3 * sizeof(int64_t));
    if ((outputKMeansDim3->points)[0].vector == NULL) return -1;
    ((outputKMeansDim3->points)[0].vector)[0] = (int64_t) -1;
    ((outputKMeansDim3->points)[0].vector)[1] = (int64_t) 4;
    ((outputKMeansDim3->points)[0].vector)[2] = (int64_t) 4;
    (outputKMeansDim3->points)[0].nearestCentroidID = 0;

    (outputKMeansDim3->points)[1].vector = malloc(3 * sizeof(int64_t));
    if ((outputKMeansDim3->points)[1].vector == NULL) return -1;
    ((outputKMeansDim3->points)[1].vector)[0] = (int64_t) -1;
    ((outputKMeansDim3->points)[1].vector)[1] = (int64_t) -2;
    ((outputKMeansDim3->points)[1].vector)[2] = (int64_t) 9;
    (outputKMeansDim3->points)[1].nearestCentroidID = 0;

    (outputKMeansDim3->points)[2].vector = malloc(3 * sizeof(int64_t));
    if ((outputKMeansDim3->points)[2].vector == NULL) return -1;
    ((outputKMeansDim3->points)[2].vector)[0] = (int64_t) 2;
    ((outputKMeansDim3->points)[2].vector)[1] = (int64_t) 4;
    ((outputKMeansDim3->points)[2].vector)[2] = (int64_t) 2;
    (outputKMeansDim3->points)[2].nearestCentroidID = 0;

    (outputKMeansDim3->points)[3].vector = malloc(3 * sizeof(int64_t));
    if ((outputKMeansDim3->points)[3].vector == NULL) return -1;
    ((outputKMeansDim3->points)[3].vector)[0] = (int64_t) 6;
    ((outputKMeansDim3->points)[3].vector)[1] = (int64_t) 2;
    ((outputKMeansDim3->points)[3].vector)[2] = (int64_t) 1;
    (outputKMeansDim3->points)[3].nearestCentroidID = 1;

    (outputKMeansDim3->points)[4].vector = malloc(3 * sizeof(int64_t));
    if ((outputKMeansDim3->points)[4].vector == NULL) return -1;
    ((outputKMeansDim3->points)[4].vector)[0] = (int64_t) -2;
    ((outputKMeansDim3->points)[4].vector)[1] = (int64_t) 4;
    ((outputKMeansDim3->points)[4].vector)[2] = (int64_t) 3;
    (outputKMeansDim3->points)[4].nearestCentroidID = 1;

    (outputKMeansDim3->points)[5].vector = malloc(3 * sizeof(int64_t));
    if ((outputKMeansDim3->points)[5].vector == NULL) return -1;
    ((outputKMeansDim3->points)[5].vector)[0] = (int64_t) 5;
    ((outputKMeansDim3->points)[5].vector)[1] = (int64_t) 5;
    ((outputKMeansDim3->points)[5].vector)[2] = (int64_t) 5;
    (outputKMeansDim3->points)[5].nearestCentroidID = 1;

    (outputKMeansDim3->centroids)[0].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim3->centroids)[0].vector == NULL) return -1;
    ((outputKMeansDim3->centroids)[0].vector)[0] = (int64_t) -2;
    ((outputKMeansDim3->centroids)[0].vector)[1] = (int64_t) 4;
    ((outputKMeansDim3->centroids)[0].vector)[1] = (int64_t) 3;

    (outputKMeansDim3->centroids)[1].vector = malloc(2 * sizeof(int64_t));
    if ((outputKMeansDim3->centroids)[1].vector == NULL) return -1;
    ((outputKMeansDim3->centroids)[1].vector)[0] = (int64_t) 6;
    ((outputKMeansDim3->centroids)[1].vector)[1] = (int64_t) 2;
    ((outputKMeansDim3->centroids)[0].vector)[1] = (int64_t) 1;


    outputStartingCentroids1 = (point_t **) malloc(sizeof(point_t *));
    outputStartingCentroids1[0] = malloc(sizeof(point_t) * 2);

    outputStartingCentroids1[0][0].vector = malloc(sizeof(int64_t) * 3);
    outputStartingCentroids1[0][0].vector[0] = (int64_t) -2;
    outputStartingCentroids1[0][0].vector[1] = (int64_t) 4;
    outputStartingCentroids1[0][0].vector[2] = (int64_t) 3;

    outputStartingCentroids1[0][1].vector = malloc(sizeof(point_t) * 3);

    outputStartingCentroids1[0][1].vector[0] = (int64_t) 6;
    outputStartingCentroids1[0][1].vector[1] = (int64_t) 2;
    outputStartingCentroids1[0][1].vector[2] = (int64_t) 1;


    outputStartingCentroids2 = (point_t **) malloc(sizeof(point_t *));
    outputStartingCentroids2[0] = malloc(sizeof(point_t) * 2);

    outputStartingCentroids2[0][0].vector = malloc(sizeof(int64_t) * 2);

    outputStartingCentroids2[0][0].vector[0] = (int64_t) 1;
    outputStartingCentroids2[0][0].vector[1] = (int64_t) 1;

    outputStartingCentroids2[0][1].vector = malloc(sizeof(point_t) * 2);

    outputStartingCentroids2[0][1].vector[0] = (int64_t) 2;
    outputStartingCentroids2[0][1].vector[1] = (int64_t) 2;

    outputFile = fopen("tests_files/output_csv/ex1.csv", "w");
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
        free(outputKMeansDim3->centroids[i].vector);
    }
    for (int i = 0; i < k; i++) {
        free(outputStartingCentroids2[0][i].vector);
        free(outputStartingCentroids1[0][i].vector);
    }
    free(outputStartingCentroids2[0]);
    free(outputStartingCentroids1[0]);

    free(outputKMeansDim2->points);
    free(outputKMeansDim2->centroids);
    free(outputKMeansDim2->clustersSize);
    free(outputKMeansDim2);

    numberOfPoints = 6;
    for (int i = 0; i < numberOfPoints; i++) {
        free(outputKMeansDim3->points[i].vector);
    }
    free(outputKMeansDim3->points);
    free((outputKMeansDim3->centroids));
    free(outputKMeansDim3->clustersSize);

    free(outputKMeansDim3);

    fclose(outputFile);

    free(outputStartingCentroids1);
    free(outputStartingCentroids2);

    return 0;
}

/**
 * We only check here if everything looks good
 * For better assessment, we've used compare_solutions.py
 */
void test_createOutputFileDimension2(void) {
    squared_distance_func_t generic_func = squared_manhattan_distance;
    runKMeans(outputKMeansDim2, (squared_distance_func_t (*)(const point_t *, const point_t *, uint32_t)) generic_func);
    writeHeadline(false, outputFile);
    point_t **clusters = generateClusters(outputKMeansDim2);
    uint64_t distortionValue = distortion(outputKMeansDim2,
                                          (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                       uint32_t)) generic_func);
    writeOneKMeans(outputKMeansDim2, false, outputFile, outputStartingCentroids2[0],
                   clusters, distortionValue);

}
