#include <stdio.h>
#include <stdlib.h>

#include "../headers/outputCsvTests.h"
#include "../../src/writeOutputFile.c"

int32_t setupCreateOutputFile(void) {

    kMeansDim2 = (kMeans_t *) malloc(sizeof(kMeans_t));
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

    kMeansDim3 = (kMeans_t *) malloc(sizeof(kMeans_t));
    if (kMeansDim3 == NULL) return -1;
    kMeansDim3->dimension = (int32_t) 3;
    kMeansDim3->points = (point_t *) malloc(6 * sizeof(point_t));
    kMeansDim3->centroids = (point_t *) malloc(2 * sizeof(point_t));
    if (kMeansDim3->points == NULL) return -1;
    kMeansDim3->size = 6;
    kMeansDim3->k = 2;
    kMeansDim3->clustersSize = (int64_t *) malloc(2 * sizeof(int64_t *));
    if (kMeansDim3->clustersSize == NULL) return -1;

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

    outputFile2 = fopen("output_csv/ex1.csv", "w");
    outputFile = fopen("output_csv/dimension3.csv", "w");

    return 0;

}


int32_t teardownCreateOutputFile(void) {
    int64_t numberOfPoints = 7;
    int32_t k = 2;
    for (int i = 0; i < numberOfPoints; i++) {
        free(kMeansDim2->points[i].vector);
    }
    for (int i = 0; i < k; i++) {
        free(kMeansDim2->centroids[i].vector);
        free(kMeansDim3->centroids[i].vector);
    }
    for (int i = 0; i < k; i++) {
        free(outputStartingCentroids2[0][i].vector);
        free(outputStartingCentroids1[0][i].vector);
    }
    free(outputStartingCentroids2[0]);
    free(outputStartingCentroids1[0]);

    free(kMeansDim2->points);
    free(kMeansDim2->centroids);
    free(kMeansDim2->clustersSize);
    free(kMeansDim2);

    numberOfPoints = 6;
    for (int i = 0; i < numberOfPoints; i++) {
        free(kMeansDim3->points[i].vector);
    }
    free(kMeansDim3->points);
    free((kMeansDim3->centroids));
    free(kMeansDim3->clustersSize);

    free(kMeansDim3);

    fclose(outputFile);
    fclose(outputFile2);

    free(outputStartingCentroids1);
    free(outputStartingCentroids2);

    return 0;
}

void test_createOutputFileDimension2(void) {
    squared_distance_func_t generic_func = squared_manhattan_distance;
    runKMeans(kMeansDim2, (squared_distance_func_t (*)(const point_t *, const point_t *, int32_t)) generic_func);
    csvFileHeadline(false, outputFile2);
    point_t **clusters = generateClusters(kMeansDim2);
    int64_t distortionValue = distortion(kMeansDim2,
                                         (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                      int32_t)) generic_func);
    writeOneKMeans(kMeansDim2, false, outputFile2, outputStartingCentroids2[0],
                   clusters, distortionValue);

}
