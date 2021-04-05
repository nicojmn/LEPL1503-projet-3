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
writeOneKMeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids,
               squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2, int32_t dimension));


#endif //CREATEOUTPUTFILE_H
