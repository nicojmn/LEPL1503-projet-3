#ifndef MANAGEHEAP_H
#define MANAGEHEAP_H

#include <stdio.h>
#include <stdbool.h>

#include "kMeans.h"
#include "buffer.h"
#include "manageArgs.h"


/**
 * Free all the data related to an instance of kMeans
 * @param KMeans : the structure we want to clean
 */
void clean(kMeans_t *KMeans);

/**
 * Free the data of all remaining structures and close what need to be closed
 * @param generalData : information collected from the input file
 * @param startingCentroids : set of starting centroids used for runKMeans calculation
 * @param iterationNumber : number of times we calculate a new instance of the kMeans problem
 * @param args : the arguments passed to the program
 * @param buffer: the buffer structure used by the threads for the producer/consumer process
 */
void fullClean(data_t *generalData, point_t **startingCentroids, uint64_t iterationNumber,
               args_t args, buffer_t *buffer);

#endif
