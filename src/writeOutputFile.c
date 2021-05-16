#include "../headers/writeOutputFile.h"

int32_t writeHeadline(bool quiet, FILE *outputFile) {
    char *dataNames = "initialization centroids,distortion,centroids";
    if (fprintf(outputFile, "%s", dataNames) < 0) return -1;

    if (!quiet) {
        char *suppDataNames = ",clusters\0";
        if (fprintf(outputFile, "%s", suppDataNames) < 0) return -1;
    }
    return 0;
}


point_t **generateClusters(kMeans_t *kMeans, bool quiet) {
    if (quiet) return NULL;

    point_t **clusters = malloc(sizeof(point_t) * kMeans->k);
    if (clusters == NULL) return NULL;

    // positionsInClusters stores the place of each last point insert into a cluster
    uint64_t *positionsInClusters = malloc(sizeof(uint64_t) * kMeans->k);
    if (positionsInClusters == NULL) return NULL;
    for (uint32_t clusterNbr = 0; clusterNbr < kMeans->k; clusterNbr++) {
        clusters[clusterNbr] = malloc(sizeof(point_t) * kMeans->clustersSize[clusterNbr]);
        if (clusters[clusterNbr] == NULL) return NULL;
        positionsInClusters[clusterNbr] = 0;
    }
    // Creation of the clusters
    for (uint64_t i = 0; i < kMeans->size; i++) {
        uint32_t ID = kMeans->points[i].nearestCentroidID;
        clusters[ID][positionsInClusters[ID]] = kMeans->points[i];
        positionsInClusters[ID]++;
    }
    free(positionsInClusters);
    return clusters;
}


int32_t writeVectorList(point_t *listOfVectors, uint32_t dimension, uint64_t size, FILE *outputFile) {

    for (uint64_t vectors = 0; vectors < size; ++vectors) {
        if (fprintf(outputFile, "(") < 0) return -1;
        for (uint32_t values = 0; values < dimension; ++values) {
            if (fprintf(outputFile, "%" PRIi64, listOfVectors[vectors].vector[values]) < 0) return -1;
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

int32_t writeOneKMeans(kMeans_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids,
                       point_t **clusters, uint64_t distortionValue) {
    // writes the starting centroids
    if (fprintf(outputPath, "\n") < 0) return -1;
    if (fprintf(outputPath, "\"[") < 0) return -1;
    if (writeVectorList(startingCentroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, "]\",") < 0) return -1;

    // writes the distortion
    if (fprintf(outputPath, "%" PRIu64, distortionValue) < 0) return -1;
    if (fprintf(outputPath, ",\"[") < 0) return -1;

    // writes the final centroids
    if (writeVectorList(kMeans->centroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, "]\"") < 0) return -1;

    // we write each points into its cluster only in non quiet mode
    if (!quiet) {
        if (fprintf(outputPath, ",\"[") < 0) return -1;
        for (uint32_t i = 0; i < kMeans->k; i++) {
            if (fprintf(outputPath, "[") < 0) return -1;
            if (writeVectorList(clusters[i], kMeans->dimension, kMeans->clustersSize[i], outputPath) < 0) return -1;
            if (fprintf(outputPath, "]") < 0) return -1;
            if (i != kMeans->k - 1) {
                if (fprintf(outputPath, ", ") < 0) return -1;
            }
        }
        if (fprintf(outputPath, "]\"") < 0) return -1;
        for (uint32_t i = 0; i < kMeans->k; ++i) {
            free(clusters[i]);
        }
    }
    free(clusters);
    return 0;
}