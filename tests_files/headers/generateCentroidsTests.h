#ifndef GENERATECENTROIDSTESTS_H
#define GENERATECENTROIDSTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kmeansStruct.h"
#include "../../headers/kMeans.h"
#include "../../headers/readBinaryFile.h"
#include "../../headers/generateStartingCentroids.h"

int32_t setupGenerateStartingCentroids(void);

int32_t teardownGenerateStartingCentroids(void);

void testGenerateStartingCentroids(void);

void testCombinatorial(void);

#endif