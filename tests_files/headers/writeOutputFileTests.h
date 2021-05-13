#ifndef OUTPUTCSVTESTS_H
#define OUTPUTCSVTESTS_H

#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kMeansStruct.h"
#include "../../headers/writeOutputFile.h"

int32_t setupCreateOutputFile(void);

int32_t teardownCreateOutputFile(void);

void test_createOutputFileDimension2(void);

#endif



