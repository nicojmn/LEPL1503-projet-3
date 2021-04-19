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
 * @param quiet : boolean that adds the clusters in the output file if equals to false
 * @param outputFile : the already opened output file
 * @return 0 if no error, -1 otherwise
 */
int32_t csvFileHeadline(bool quiet, FILE *outputFile);

/**
 * Write a list of vectors into the outputFile
 * @param listOfVectors : malloced structure
 * @param dimension : number of dimensions
 * @param size : number of points in a
 * @param outputFile : the already opened output file
 * @return 0 if no error, -1 otherwise
 */
int32_t writeVectorList(point_t *listOfVectors, uint32_t dimension, uint32_t size, FILE *outputFile);

/**
 * Function used to write one execution of Kmeans
 * @param kMeans : the kMeans we want to write about
 * @param quiet : boolean that adds the clusters in the output file if equals to false
 * @param outputPath : the already opened output file
 * @param startingCentroids : set of points used for kMeans calculation
 * @param distanceFunction : the formula used to calculate points distances, either the manhattan or the euclidean one
 * @return 0 if no error, -1 otherwise
 */
int32_t writeOneKMeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids,
                       squared_distance_func_t distanceFunction(const point_t *p1, const point_t *p2,
                                                                int32_t dimension));


#endif
