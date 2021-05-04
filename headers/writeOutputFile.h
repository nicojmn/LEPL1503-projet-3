#ifndef WRITEOUTPUTFILE_H
#define WRITEOUTPUTFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "inttypes.h"
#include <sys/types.h>
#include <unistd.h>

#include "kMeans.h"
#include "distance.h"


/**
 * Writes the headline of the csv outputFile1
 * @param quiet : boolean that decides whether we want to write the points of the simulation
 *                in the output csv file or not
 * @param outputFile : an already opened output csv file
 * @return 0 if no error, -1 otherwise
 */
int32_t writeHeadline(bool quiet, FILE *outputFile);

/**
 * @param kMeans : one instance of the problem kMeans
 * @param quiet: boolean that decides whether we want to write the points of the simulation
 *                in the output csv file or not
 * @return : returns the final clusters of kMeans
 */
point_t **generateClusters(kMeans_t *kMeans, bool quiet);

/**
 * Write a list of vectors into the outputFile1
 * @param listOfVectors : malloced structure
 * @param dimension : the dimension of each point
 * @param size : size of listOfVectors
 * @param outputFile : an already opened output csv file
 * @return 0 if no error, -1 otherwise
 */
int32_t writeVectorList(point_t *listOfVectors, uint32_t dimension, uint64_t size, FILE *outputFile);


/**
 * Function used to write one instance of kMeans
 * @param kMeans : the instance of kMeans we want to write into outputFile1
 * @param quiet : boolean that decides whether we want to write the points of the simulation
 *                in the output csv file or not
 * @param outputFile : an already opened output csv file
 * @param startingCentroids : the different set of starting centroids
 * @param clusters : the final clusters of the kMeans instance
 * @param distortionValue: the distortion of kMeans
 * @return 0 if no error, -1 otherwise
 */
int32_t writeOneKMeans(kMeans_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids,
                       point_t **clusters, uint64_t distortionValue);

#endif