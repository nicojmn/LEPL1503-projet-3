#ifndef GENERATESTARTINGCENTROIDS_H
#define GENERATESTARTINGCENTROIDS_H

#include <stdint.h>
#include "point.h"

uint64_t factorial(uint32_t x);


uint64_t combinatorial(uint32_t n, uint32_t x);

/**
 *
 * @param startingCentroidsID: malloced array of array of point_t corresponding
 * @param vectors : the points of the simulation
 * @param k : number of centroid
 * @param n : the n first points which will be used for the combination
 * @param iterationNbr : #TODO
 *        //What does it do #TODO
 */
void generateSetOfStartingCentroids(point_t **startingCentroidsID, int64_t **vectors,
                                    int32_t k, int32_t n, int32_t iterationNbr);


#endif //GENERATESTARTINGCENTROIDS_H