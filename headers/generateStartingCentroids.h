#ifndef GENERATESTARTINGCENTROIDS_H
#define GENERATESTARTINGCENTROIDS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "kMeansStruct.h"

/**
 * Calculate a factorial number
 * @param x : a number
 * @return the factorial of x
 */
uint64_t factorial(uint64_t x);

/**
 * Calculate a combinatorial
 * We use a special function for numerical consideration
 * It won't overflow for close big number kCentroids and n
 * in fact it does the simplification (200!) / (198!2!) = (200*199) / (2!)
 * @param nFirstPoints : total number of items
 * @param kCentroids : number of items being picked
 * @return the combinatorial of n with x items being picked
 */
uint64_t combinatorial(uint32_t nFirstPoints, uint32_t kCentroids);

/**
 * Generate a set of starting centroids (vectors) inside startingCentroidsID
 * @param startingCentroidsID: malloced array of array of point_t
 * @param vectors : the points of the simulation
 * @param kCentroids : number of centroid
 * @param nFirstPoints : the nFirstPoints first points which will be used for the combination
 * @param iterationNbr : number of times we'll calculate a new instance of kMeans
 */
int32_t generateSetOfStartingCentroids(point_t **startingCentroidsID, int64_t **vectors,
                                       uint32_t kCentroids, uint32_t nFirstPoints, uint64_t iterationNbr);

#endif