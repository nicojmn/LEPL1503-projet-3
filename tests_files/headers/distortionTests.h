#ifndef DISTORTIONTESTS_H
#define DISTORTIONTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kMeans.h"

/**
 * Function to prepare tests (malloc(), assigning variables)
 * @return 0 if everything goes well, -1 if an error occurs
 */
int32_t distortionSetup(void);

/**
 * Function to clean memory after tests
 * @return 0
 */
int32_t distortionTeardown(void);

/**
 * CUnit tests to check distortion
 */
void testDistortion(void);


#endif
