#ifndef GENERATESTARTINGCENTROIDS_H
#define GENERATESTARTINGCENTROIDS_H

#include <stdint.h>
#include "kmeansStruct.h"

/**
 * @param x
 * @return #TODO Faire la signature
 */
uint64_t factorial(uint32_t x);

/** We use a special function for numerical consideration
 It won't overflow for close big number k and n*/
uint64_t combinatorial(uint32_t n, uint32_t x);

/**
 *
 * @param startingCentroidsID: malloced array of array of point_t corresponding
 * @param vectors : the points of the simulation
 * @param k : number of centroid
 * @param n : the n first points which will be used for the combination
 * @param iterationNbr : #TODO C'est quoi iterationNbr ?
 *        //What does it do #TODO Ecrire ce que la fonction fait
 */
void generateSetOfStartingCentroids(point_t **startingCentroidsID, int64_t **vectors,
                                    uint32_t k, uint32_t n, uint64_t iterationNbr);


#endif