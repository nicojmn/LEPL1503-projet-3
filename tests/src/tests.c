#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/distance.h"
#include "../../headers/kmeansStruct.h"
#include "../../headers/kMeans.h"
#include "../../src/distance.c"
#include "../../src/kMeans.c"
#include "../../src/generateStartingCentroids.c"
#include "../../headers/readBinaryFile.h"
#include "../../src/readBinaryFile.c"
#include "../../src/distortion.c"

#include "../headers/tests.h"
#include "../headers/distanceTests.h"
#include "./distanceTests.c"
#include "../headers/readBinaryFileTests.h"
#include "./readBinaryFileTests.c"
#include "../headers/distortionTests.h"
#include "./distortionTests.c"
#include "../headers/outputCsvTests.h"
#include "./outputCsvTests.c"
#include "../headers/assignVectorTests.h"
#include "./assignVectorTests.c"
#include "../headers/updateCentroidsTests.h"
#include "./updateCentroidsTests.c"
#include "../headers/kMeansTests.h"
#include "./kMeansTests.c"
#include "../headers/generateCentroidsTests.h"
#include "./generateCentroidsTests.c"


int main() {

    CU_pSuite distanceTestSuite = NULL;
    CU_pSuite distortionTestSuite = NULL;
    CU_pSuite updateCentroidsTestSuite = NULL;
    CU_pSuite assignVectorSuite = NULL;
    CU_pSuite kmeansSuite = NULL;
    CU_pSuite binaryFileSuite = NULL;
    CU_pSuite csvFileSuite = NULL;
    CU_pSuite generateStartingCentroidsSuite = NULL;

    /** initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /** add a suite to the registry */
    distanceTestSuite = CU_add_suite("distance tests", distanceSetup, distanceTeardown);
    distortionTestSuite = CU_add_suite("distortion test", distortionSetup, distortionTeardown);
    generateStartingCentroidsSuite = CU_add_suite("generateStartingCentroids test", setupGenerateStartingCentroids,
                                                  teardownGenerateStartingCentroids);
    updateCentroidsTestSuite = CU_add_suite("updateCentroids test", updateCentroidsSetup, updateCentroidsTeardown);
    assignVectorSuite = CU_add_suite("Assign vector", assignVectorSetup, assignVectorTeardown);
    kmeansSuite = CU_add_suite("Kmeans test", kMeansSetup, kMeansTeardown);
    binaryFileSuite = CU_add_suite("binary file loading test", setupBinaryFile, teardownBinaryFile);
    csvFileSuite = CU_add_suite("writing into csv file", setupCreateOutputFile, teardownCreateOutputFile);

    if (distanceTestSuite == NULL || distortionTestSuite == NULL ||
        updateCentroidsTestSuite == NULL || assignVectorSuite == NULL || kmeansSuite == NULL
        || binaryFileSuite == NULL || csvFileSuite == NULL || generateStartingCentroidsSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** add the tests to the suite */
    /** NOTE - ORDER IS IMPORTANT */
    if ((NULL == CU_add_test(distanceTestSuite, "squared manhattan distance", testManhattan)) ||
        (NULL == CU_add_test(distanceTestSuite, "squared euclidean distance", testEuclidean)) ||
        (NULL == CU_add_test(distortionTestSuite, "distortion", testDistortion)) ||
        (NULL ==
         CU_add_test(generateStartingCentroidsSuite, "generation of starting centroids",
                     testGenerateStartingCentroids)) ||
        (NULL == CU_add_test(updateCentroidsTestSuite, "updateCentroids", testUpdateCentroids)) ||
        (NULL == CU_add_test(assignVectorSuite, "assign vector normal", testNormalAssignVectorToCentroids)) ||
        (NULL == CU_add_test(assignVectorSuite, "assign vector first", testFirstAssignVectorToCentroids)) ||
        (NULL == CU_add_test(kmeansSuite, "One iteration of Kmeans", testKmeansDimension2)) ||
        (NULL == CU_add_test(binaryFileSuite, "Test of loadingData", testReadBinaryFile)) ||
        (NULL == CU_add_test(csvFileSuite, "test of writing into csv", test_createOutputFileDimension2))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}