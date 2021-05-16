#ifndef ASSIGNVECTORTESTS_H
#define ASSIGNVECTORTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kMeans.h"

/**
 * Function to prepare our vectors tests (setup memory and variables)
 * @return 0 if everything goes well, -1 if an error occurs
 */
int32_t assignVectorSetup(void);

/**
 * Function to clean memory after performing vectors tests
 * @return 0
 */
int32_t assignVectorTeardown(void);


/**
 * CUnit tests to check if assignation of vectors is correct in a normal case
 */
void testNormalAssignVectorToCentroids(void);

/**
 * CUnit tests to check if assignation is correct in all case
 */
void testFirstAssignVectorToCentroids(void);

#endif
