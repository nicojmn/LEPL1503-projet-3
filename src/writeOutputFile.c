#include <sys/types.h>
#include <unistd.h>

#include "../headers/writeOutputFile.h"

// TODO make tests for csvFileHeadline function
int32_t csvFileHeadline(bool quiet, FILE *outputFile) {
    char *dataNames = "initialization centroids,distortion,centroids";
    fprintf(outputFile, "%s", dataNames);

    if (!quiet) {
        char *suppDataNames = ",clusters\0";
        fprintf(outputFile, "%s", suppDataNames);
    }
    return 0;
}


point_t **generateClusters(kMeans_t *kMeans) {
    point_t **clusters = malloc(sizeof(point_t) * kMeans->k);
    if (clusters == NULL) return NULL;

    uint64_t *clustersIndexes = malloc(sizeof(uint64_t) * kMeans->k);
    for (int64_t clusterNbr = 0; clusterNbr < kMeans->k; clusterNbr++) {
        clusters[clusterNbr] = malloc(sizeof(point_t) * kMeans->clustersSize[clusterNbr]);
        if (clusters[clusterNbr] == NULL) return NULL;
        clustersIndexes[clusterNbr] = 0;
    }
    for (int i = 0; i < kMeans->size; i++) {
        int32_t ID = kMeans->points[i].nearestCentroidID;
        clusters[ID][clustersIndexes[ID]] = kMeans->points[i];
        clustersIndexes[ID]++;
    }
    free(clustersIndexes);
    return clusters;
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

int32_t writeOneKMeans(kMeans_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids,
                       point_t **clusters, int64_t distortionValue) {

    if (fprintf(outputPath, "\n") < 0) return -1;
    if (fprintf(outputPath, "\"[") < 0) return -1;
    if (writeVectorList(startingCentroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, "]\",") < 0) return -1;
    if (fprintf(outputPath, "%li,", distortionValue) < 0) return -1;
    if (fprintf(outputPath, "\"[") < 0) return -1;
    if (writeVectorList(kMeans->centroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, "]\"") < 0) return -1;
    if (!quiet) {
        if (fprintf(outputPath, ",") < 0) return -1;
        if (fprintf(outputPath, "\"[") < 0) return -1;

        for (int i = 0; i < kMeans->k; i++) {
            if (fprintf(outputPath, "[") < 0) return -1;
            if (writeVectorList(clusters[i], kMeans->dimension, kMeans->clustersSize[i], outputPath) < 0) return -1;
            if (fprintf(outputPath, "]") < 0) return -1;
            if (i != kMeans->k - 1) {
                if (fprintf(outputPath, ", ") < 0) return -1;
            }
        }
        if (fprintf(outputPath, "]\"") < 0) return -1;

        for (int i = 0; i < kMeans->k; ++i) {
            free(clusters[i]);
        }
        free(clusters);
    }
    return 0;
}