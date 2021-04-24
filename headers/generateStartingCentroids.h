#ifndef GENERATESTARTINGCENTROIDS_H
#define GENERATESTARTINGCENTROIDS_H

#include <stdint.h>
#include "kmeansStruct.h"

/**
 * Calculate a factorial number
 * @param x : a number
 * @return the factorial of x
 */
uint64_t factorial(uint64_t x);

/**
 * Calculate a combinatorial
 * We use a special function for numerical consideration
 * It won't overflow for close big number k and n
 * @param n : total number of items
 * @param x : number of items being picked
 * @return the combinatorial of n with x items being picked
 */
uint64_t combinatorial(uint32_t n, uint32_t x);

/**
 * Generate a set of starting centroids (vectors) inside startingCentroidsID
 * @param startingCentroidsID: malloced array of array of point_t corresponding
 * @param vectors : the points of the simulation
 * @param k : number of centroid
 * @param n : the n first points which will be used for the combination
 * @param iterationNbr : number of times we'll calculate new centroids
 */
void generateSetOfStartingCentroids(point_t **startingCentroidsID, int64_t **vectors,
                                    uint32_t k, uint32_t n, uint64_t iterationNbr);


#endif