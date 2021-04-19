#ifndef CREATEOUTPUTFILE_H
#define CREATEOUTPUTFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "kMeans.h"
#include "distance.h"


/**
 * Writes in the output file the names of the data that will be added later
 * @param quiet
 * @param outputPath
 * @return 0 if no error, -1 otherwise
 */
int32_t csvFileHeadline(bool quiet, FILE *outputPath);

/**
 * Write a list of vectors into the outputFile
 * @param listOfVectors
 * @param dimension
 * @param size
 * @param outputFile
 * @return 0 if no error, -1 otherwise
 */
int32_t writeVectorList(point_t *listOfVectors, uint32_t dimension, uint32_t size, FILE *outputFile);

/**
 * Function used to write one execution of Kmeans
 * @param kMeans
 * @param quiet
 * @param outputPath
 * @param startingCentroids
 * @param distanceFunction
 * @return 0 if no error, -1 otherwise
 */
int32_t writeOneKMeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids,
                       squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2,
                                                                int32_t dimension));


#endif
