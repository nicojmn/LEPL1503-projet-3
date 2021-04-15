#include <sys/types.h>
#include <unistd.h>

#include "../headers/createOutputFile.h"

// TODO make tests for csvFileHeadline function
int32_t csvFileHeadline(bool quiet, FILE *outputPath) {
    char *dataNames = "initialization centroids,distortion,centroids";
    fprintf(outputPath, "%s", dataNames);

    if (!quiet) {
        char *suppDataNames = ",clusters\0";
        fprintf(outputPath, "%s", suppDataNames);
    }
    return 0;
}

// TODO : make tests
int32_t writeVectorList(point_t *listOfVectors, uint32_t dimension, uint32_t size, FILE *outputFile) {

    for (int vectors = 0; vectors < size; ++vectors) {
        if (fprintf(outputFile, "(") < 0) return -1;
        for (int values = 0; values < dimension; ++values) {
            if (fprintf(outputFile, "%ld", listOfVectors[vectors].vector[values]) < 0) return -1;
            if (values != dimension - 1) {
                if (fprintf(outputFile, ", ") < 0) return -1;
            }
        }
        if (vectors != size - 1) {
            if (fprintf(outputFile, "), ") < 0) return -1;
        } else {
            if (fprintf(outputFile, ")") < 0) return -1;
        }
    }
    return 0;
}

//TODO make tests for writeOneKMeans function

int32_t writeOneKMeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids,
                       squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2,
                                                                int32_t dimension)) {


    if (fprintf(outputPath, "\n") < 0) return -1;
    if (fprintf(outputPath, "\"[") < 0) return -1;
    if (writeVectorList(startingCentroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, "]\",") < 0) return -1;
    if (fprintf(outputPath, "%li,", distortion(kMeans, distanceFunction)) < 0) return -1;
    if (fprintf(outputPath, "\"[") < 0) return -1;
    if (writeVectorList(kMeans->centroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, "]\"") < 0) return -1;
    if (!quiet) {
        if (fprintf(outputPath, ",") < 0) return -1;
        if (fprintf(outputPath, "\"[") < 0) return -1;
        point_t **listOfVector = malloc(sizeof(point_t) * kMeans->k);
        if (listOfVector == NULL) return -1;

        uint64_t *listOfSizes = malloc(sizeof(uint64_t) * kMeans->k);
        for (int64_t clusterNbr = 0; clusterNbr < kMeans->k; clusterNbr++) {
            listOfVector[clusterNbr] = malloc(sizeof(point_t) * kMeans->clustersSize[clusterNbr]);
            if (listOfVector[clusterNbr] == NULL) return -1;
            listOfSizes[clusterNbr] = 0;
        }
        for (int i = 0; i < kMeans->size; i++) {
            int32_t ID = kMeans->points[i].nearestCentroidID;
            listOfVector[ID][listOfSizes[ID]] = kMeans->points[i];
            listOfSizes[ID]++;
        }
        for (int i = 0; i < kMeans->k; i++) {
            if (fprintf(outputPath, "[") < 0) return -1;
            if (writeVectorList(listOfVector[i], kMeans->dimension, kMeans->clustersSize[i], outputPath) < 0) return -1;
            if (fprintf(outputPath, "]") < 0) return -1;
            if (i != kMeans->k - 1) {
                if (fprintf(outputPath, ", ") < 0) return -1;
            }
        }
        if (fprintf(outputPath, "]\"") < 0) return -1;

        free(listOfSizes);
        for (int i = 0; i < kMeans->k; ++i) {
            free(listOfVector[i]);
        }
        free(listOfVector);
    }
    return 0;
}