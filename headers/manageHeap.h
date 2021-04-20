#ifndef MANAGEHEAP_H
#define MANAGEHEAP_H

#include <stdio.h>
#include <stdbool.h>
#include "kMeans.h"
#include "manageArgs.h"


/**
 * Free all the data allocated in a k_means_t structure
 * @param KMeans : the structure we want to clean
 */
void clean(k_means_t *KMeans);

/**
 * Free the data of the global structures of the program
 * @param generalData : the instance's characteristics and all the points from the input file
 * @param startingCentroids : set of points used for kMeans calculation
 * @param iterationNumber : number of times we calculate new centroids
 * @param args : the arguments of the program
 */
void fullClean(data_t *generalData, point_t **startingCentroids, uint64_t iterationNumber, args_t args);

#endif
