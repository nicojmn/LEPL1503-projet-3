#ifndef UPDATECENTROIDSTESTS_H
#define UPDATECENTROIDSTESTS_H

#include "../../headers/kMeansStruct.h"
#include "../../headers/kMeans.h"

/**
 * Function to prepare tests (malloc(), assigning variables)
 * @return 0 if everything goes well, -1 if an error occurs
 */
int32_t updateCentroidsSetup(void);

/**
 * Function to clean memory after tests
 * @return 0
 */
int32_t updateCentroidsTeardown(void);

void testUpdateCentroids(void);

#endif // UPDATECENTROIDSTESTS_H
