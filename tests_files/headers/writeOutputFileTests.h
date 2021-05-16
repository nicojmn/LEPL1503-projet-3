#ifndef OUTPUTCSVTESTS_H
#define OUTPUTCSVTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kMeansStruct.h"
#include "../../headers/writeOutputFile.h"

/**
 * Function to prepare tests (malloc(), assigning variables)
 * @return 0 if everything goes well, -1 if an error occurs
 */
int32_t setupCreateOutputFile(void);

/**
 * Function to clean memory after tests
 * @return 0
 */
int32_t teardownCreateOutputFile(void);

/**
 * check if output file is write correctly
 */
void test_createOutputFileDimension2(void);

#endif



