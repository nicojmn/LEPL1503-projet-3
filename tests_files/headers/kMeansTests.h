#ifndef KMEANSTESTS_H
#define KMEANSTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kmeansStruct.h"
#include "../../headers/kMeans.h"

int32_t kMeansSetup(void);

int32_t kMeansTeardown(void);

void testKMeansDimension2(void);


#endif //PROJET_CMAKE_KMEANSTESTS_H
