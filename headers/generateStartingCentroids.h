#ifndef GENERATESTARTINGCENTROIDS_H
#define GENERATESTARTINGCENTROIDS_H
#include <stdint.h>
#include "point.h"

int64_t factorial(int64_t x);


/**
 *
 * @param startingCentroidsID: malloced array of array of point_t corresponding
 * @param vectors : the points of the simulation
 * @param k : number of centroid
 * @param n : the n first points which will be used for the combination
 */
void generateSetOfStartingCentroids(point_t **startingCentroidsID, int64_t **vectors,
                                    int32_t k, int32_t n, int32_t iterationNbr);


#endif //GENERATESTARTINGCENTROIDS_H