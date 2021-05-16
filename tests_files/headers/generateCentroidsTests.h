#ifndef GENERATECENTROIDSTESTS_H
#define GENERATECENTROIDSTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kMeansStruct.h"
#include "../../headers/kMeans.h"
#include "../../headers/readBinaryFile.h"
#include "../../headers/generateStartingCentroids.h"

/**
 * Function to prepare tests (malloc(), assigning variables)
 * @return 0 if everything goes well, -1 if an error occurs
 */
int32_t setupGenerateStartingCentroids(void);

/**
 * Function to clean memory after tests
 * @return 0
 */
int32_t teardownGenerateStartingCentroids(void);

/**
 * Function to test generation of centroids
 */
void testGenerateStartingCentroids(void);

/**
 * Check computation of combinatorial
 */
void testCombinatorial(void);

#endif