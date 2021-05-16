#ifndef TESTS_H
#define TESTS_H

#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>


#include "distanceTests.h"
#include "distortionTests.h"
#include "writeOutputFileTests.h"
#include "assignVectorTests.h"
#include "updateCentroidsTests.h"
#include "kMeansTests.h"
#include "generateCentroidsTests.h"
#include "readBinaryFileTests.h"
#include "compareWithPythonTests.h"

/**
 * Main function takes all tests and compute them with help of CUnit
 * @return 0 (and print summary of tests) or -1 if an error occurs
 */
int main();

#endif
