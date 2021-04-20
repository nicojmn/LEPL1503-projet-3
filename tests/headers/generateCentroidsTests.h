#ifndef PROJET_CMAKE_GENERATECENTROIDSTESTS_H
#define PROJET_CMAKE_GENERATECENTROIDSTESTS_H

#include "../../headers/generateStartingCentroids.h"
#include "../../headers/readBinaryFile.h"
#include "../headers/readBinaryFileTests.h"
#include "tests.h"

int32_t setupGenerateStartingCentroids(void);

int32_t teardownGenerateStartingCentroids(void);

void testGenerateStartingCentroids(void);


#endif