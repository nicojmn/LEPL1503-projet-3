#include "../headers/createOutputFile.h"
#include <sys/types.h>
#include <unistd.h>

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

//TODO make tests for writeOneKmeans function
int32_t writeOneKmeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids,
                       squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2,
                                                                int32_t dimension)) {
    //TODO add function csvFileHeadline for first line
    if (fprintf(outputPath, "\n") < 0) return -1;
    if (fprintf(outputPath, "\"[") < 0) return -1;
    if (writeVectorList(startingCentroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, "]\",") < 0) return -1;
    if (fprintf(outputPath, "%li,", distortion(kMeans, distanceFunction)) < 0) return -1;
    if (fprintf(outputPath, "\"[") < 0) return -1;
    if (writeVectorList(kMeans->centroids, kMeans->dimension, kMeans->k, outputPath) < 0) return -1;
    if (fprintf(outputPath, "]\"") < 0) return -1;
    if (fprintf(outputPath, ",") < 0) return -1;
    if (!quiet) {
        if (fprintf(outputPath, "\"[") < 0) return -1;
        for (int64_t clusterNbr = 0; clusterNbr < kMeans->k; clusterNbr++) {
            printf("\nsize of cluster %ld :%ld\n", clusterNbr, kMeans->clustersSize[clusterNbr]);
            point_t *listOfvector = malloc(sizeof(point_t) * kMeans->clustersSize[clusterNbr]);
            if (listOfvector == NULL) return -1;
            int index = 0;
            for (int i = 0; i < kMeans->size; i++) {
                if (kMeans->points[i].nearestCentroidID == clusterNbr) {
                    listOfvector[index] = kMeans->points[i];
                    index++;
                }
            }
            printf("%ld\n", listOfvector[2].vector[0]);
            if (fprintf(outputPath, "[") < 0) return -1;
            writeVectorList(listOfvector, kMeans->dimension, kMeans->clustersSize[clusterNbr], outputPath);
            free(listOfvector);
            if (fprintf(outputPath, "]") < 0) return -1;
            if (clusterNbr != kMeans->k - 1) {
                if (fprintf(outputPath, ", ") < 0) return -1;
            }
        }
        if (fprintf(outputPath, "]\"") < 0) return -1;
    }
    return 0;
}