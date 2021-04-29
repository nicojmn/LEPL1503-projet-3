#ifndef ASSIGNVECTORTESTS_H
#define ASSIGNVECTORTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kMeans.h"

int32_t assignVectorSetup(void);

int32_t assignVectorTeardown(void);

void testNormalAssignVectorToCentroids(void);

void testFirstAssignVectorToCentroids(void);

#endif
