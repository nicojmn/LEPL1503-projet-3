//
// Created by pierre on 02.04.21.
//

#include "../headers/createOutputFile.h"

//TODO make tests for csvFileHeadline function
void csvFileHeadline(bool quiet, FILE *outputPath){
    char *dataNames = malloc(46*sizeof(char));
    dataNames = "initialization centroids,distortion,centroids";
    fprintf(outputPath, "%s", dataNames);

    if (!quiet) {
        char *suppDataNames = malloc(9*sizeof(char));
        suppDataNames = ",clusters";
        fprintf(outputPath, "%s", suppDataNames);
        free(suppDataNames);
    }

    free(dataNames);
}

//TODO make tests for writeOneKmeans function
void writeOneKmeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids, int32_t iterationNumber){
    /*int64_t **startingCentroids = malloc(sizeof(int64_t)*(kMeans->dimension)*(kMeans->k));
    for (int i = 0; i < kMeans->k; ++i) {
        char *vector = malloc();
        for (int j = 0; j < kMeans->dimension; ++j) {

        }
    }
     fprintf(outputPath, "\"[(1, 1), (2, 2)]\",", );

    //TODO malloc all elements to write, format and write them

    fprintf(outputPath,"\n");

    free(toWrite); */
}