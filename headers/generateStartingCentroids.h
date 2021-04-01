#ifndef GENERATESTARTINGCENTROIDS_H
#define GENERATESTARTINGCENTROIDS_H

#include <stdint.h>
#include "point.h"

int64_t factorial(int64_t x);


/**
 *
 * @param startingCentroidsID: malloced array of array of point_t corresponding
 * @param vectors : The points of the simulation
 * @param k : Number of centroid
 * @param n : The n first points which will be used for the combination
 */
void generate(point_t **startingCentroidsID, int64_t **vectors, int32_t k, int32_t n);


#endif //GENERATESTARTINGCENTROIDS_H