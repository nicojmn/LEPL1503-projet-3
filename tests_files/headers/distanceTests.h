#ifndef DISTANCETESTS_H
#define DISTANCETESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/distance.h"

int32_t distanceSetup(void);

int32_t distanceTeardown(void);

void testManhattan(void);

void testEuclidean(void);

#endif
