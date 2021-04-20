#ifndef WRITEOUTPUTFILE_H
#define WRITEOUTPUTFILE_H
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

point_t **generateClusters(k_means_t *kMeans);

/**
 * Write a list of vectors into the outputFile
 * @param listOfVectors : malloced structure
 * @param dimension : number of dimensions
 * @param size : number of points in a
 * @param outputFile : the already opened output file
 * @return 0 if no error, -1 otherwise
 */
int32_t writeVectorList(point_t *listOfVectors, uint32_t dimension, uint32_t size, FILE *outputFile);


// TODO: update specification
/**
 * Function used to write one execution of Kmeans
 * @param kMeans : the kMeans we want to write about
 * @param quiet : boolean that adds the clusters in the output file if equals to false
 * @param outputFile : the already opened output file
 * @param startingCentroids : set of points used for kMeans calculation
 * @param distanceFunction : the formula used to calculate points distances, either the manhattan or the euclidean one
 * @return 0 if no error, -1 otherwise
 */
int32_t writeOneKMeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids,
                       point_t **clusters, int64_t distortionValue);


#endif
