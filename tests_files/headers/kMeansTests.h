#ifndef KMEANSTESTS_H
#define KMEANSTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kMeansStruct.h"
#include "../../headers/kMeans.h"

/**
 * Function to prepare tests (malloc(), assigning variables)
 * @return 0 if everything goes well, -1 if an error occurs
 */
int32_t kMeansSetup(void);

/**
 * Function to clean memory after tests
 * @return 0
 */
int32_t kMeansTeardown(void);

void testKMeansDimension2(void);


#endif //KMEANSTESTS_H
