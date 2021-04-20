#ifndef MANAGEHEAP_H
#define MANAGEHEAP_H

#include <stdio.h>
#include <stdbool.h>
#include "kMeans.h"
#include "manageArgs.h"


typedef struct {
    kMeans_t **kMeansInstances;
    int64_t *distortionValues;
    point_t ***clustersOfInstances;
    uint32_t *indexes;
    uint8_t head; // free place
    uint8_t tail; // oldest input
} buffer_t;

/**
 *
 * @param bufferSize
 * @return the buffer used by our threads in the producer/consumer process
 */
buffer_t *createBuffer(uint8_t bufferSize);

/**
 * Free all the data allocated in a kMeans_t structure
 * @param KMeans : the structure we want to clean
 */
void clean(kMeans_t *KMeans);

/**
 * Free the data of the global structures of the program
 * @param generalData : the instance's characteristics and all the points from the input file
 * @param startingCentroids : set of points used for runKMeans calculation
 * @param iterationNumber : number of times we calculate new centroids
 * @param args : the arguments of the program
 * @param buffer: the buffer used by the threads
 */
void
fullClean(data_t *generalData, point_t **startingCentroids, uint64_t iterationNumber, args_t args, buffer_t *buffer);

#endif
