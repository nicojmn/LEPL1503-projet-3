#ifndef PROJET_CMAKE_GENERATECENTROIDSTESTS_H
#define PROJET_CMAKE_GENERATECENTROIDSTESTS_H

#include "./tests.h"
#include "../../headers/generateStartingCentroids.h"
#include "../../headers/readBinaryFile.h"


int32_t setupGenerateStartingCentroids(void);

int32_t teardownGenerateStartingCentroids(void);

void testGenerateStartingCentroids(void);


#endif