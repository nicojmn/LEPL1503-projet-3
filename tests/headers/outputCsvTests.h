#ifndef LEPL1503_2021_SKELETON_OUTPUTCSVTESTS_H
#define LEPL1503_2021_SKELETON_OUTPUTCSVTESTS_H

#include "./tests.h"

point_t **outputStartingCentroids1;
point_t **outputStartingCentroids2;
/** Testing output file */
FILE *outputFile;
FILE *outputFile2;

int32_t setupCreateOutputFile(void);

int32_t teardownCreateOutputFile(void);

void test_createOutputFileDimension3(void);

void test_createOutputFileDimension2(void);

#endif



