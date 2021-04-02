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
void csvFileHeadline(bool quiet, FILE *outputPath);

/*
 * Adds to outputPath the following data on one line :
 */
void writeOneKmeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids, int32_t iterationNumber);

#endif //CREATEOUTPUTFILE_H
