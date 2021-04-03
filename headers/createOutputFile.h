//
// Created by pierre on 02.04.21.
//

#ifndef CREATEOUTPUTFILE_H
#define CREATEOUTPUTFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "kMeans.h"
#include "distance.h"

/*
 * Writes in the output file the names of the data that will be added later
 */
int32_t csvFileHeadline(bool quiet, FILE *outputPath);

/*
 * Adds to outputPath the following data on one line :
 */
int32_t
writeOneKmeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids, int32_t iterationNumber);

char *formatVectorList(point_t *listOfVectors, uint64_t size, uint32_t dimension, uint32_t k);

#endif //CREATEOUTPUTFILE_H
