#ifndef DISTANCETESTS_H
#define DISTANCETESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/distance.h"

/**
 * Function to prepare tests (malloc(), assigning variables)
 * @return 0 if everything goes well, -1 if an error occurs
 */
int32_t distanceSetup(void);

/**
 * Function to clean memory after tests
 * @return 0
 */
int32_t distanceTeardown(void);

/**
 * CUnit tests to check if our program compute manhattan distance correctly
 */
void testManhattan(void);

/**
 * CUnit tests to checks if our program compute euclidean distance correctly
 */
void testEuclidean(void);

#endif
