#include "../headers/createOutputFile.h"

//TODO make tests for csvFileHeadline function
int32_t csvFileHeadline(bool quiet, FILE *outputPath) {
    char *dataNames = malloc(46 * sizeof(char));
    if (dataNames == NULL) return -1;
    dataNames = "initialization centroids,distortion,centroids"; /*45*/
    fprintf(outputPath, "%s", dataNames);

    if (!quiet) {
        char *suppDataNames = malloc(10 * sizeof(char));
        if (suppDataNames == NULL) return -1;
        suppDataNames = ",clusters\0";
        fprintf(outputPath, "%s", suppDataNames);
        free(suppDataNames);
    }

    free(dataNames);
    return 0;
}

// TODO : make tests
int32_t writeVectorList(point_t *listOfVectors, uint32_t dimension, uint32_t k, FILE *outputFile) {
    if (fprintf(outputFile, "\"[") < 0) return -1;
    for (int vectors = 0; vectors < k; ++vectors) {
        if (fprintf(outputFile, "(") < 0) return -1;
        if (vectors != 0) fprintf(outputFile, ", ");
        for (int values = 0; values < dimension; ++values) {
            if (fprintf(outputFile, "%li", listOfVectors[vectors].vector[values]) < 0) return -1;
        }
        if (fprintf(outputFile, ")") < 0) return -1;
    }
    if (fprintf(outputFile, "]\"") < 0) return -1;
    return 0;
}

//TODO make tests for writeOneKmeans function
int32_t
writeOneKmeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids, int32_t iterationNumber,
               squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2, int32_t dimension)) {
    fprintf(outputPath, "\n");
    if (writeVectorList(startingCentroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, ", ") < 0) return -1;
    if (fprintf(outputPath, "%li, ", distortion(kMeans, distanceFunction)) < 0) return -1;
    if (writeVectorList(kMeans->centroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, "[") < 0) return -1;
    if (writeVectorList(startingCentroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, ", ") < 0) return -1;
    for (int64_t i = 0; i < kMeans->clustersSize; i++) {
        point_t *listOfvector = malloc(sizeof(point_t) * kMeans->clustersSize[i]);
        if (listOfvector == NULL) return -1;
        int index = 0;
        for (int j = 0; j < kMeans->size; j++) {
            if (kMeans->points[j].nearestCentroidID == i) {
                listOfvector[index] = kMeans->points[j];
                index++;
            }
        }
        writeVectorList(listOfvector, kMeans->dimension, kMeans->k, outputPath);
        if ((int64_t) i != kMeans->clustersSize - 1) {
            if (fprintf(outputPath, ", ") < 0) return -1;
        }
    }
    if (fprintf(outputPath, "]\"") < 0) return -1;
    return 0;
}