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

// TODO refactor test.c in multiples files

point_t **startingCentroids1;
point_t **startingCentroids2;

int32_t setupGenerateStartingCentroids(void) {

    dataTest1 = (data_t *) malloc(sizeof(data_t));
    if (dataTest1 == NULL) return -1;
    fileForTest1 = fopen("input_binary/ex1.bin", "r");
    loadData(fileForTest1, dataTest1);

    uint32_t k = 2;
    uint32_t n = 4;
    // We use a special function for numerical consideration
    // It won't overflow for close big number k and n
    uint64_t iterationNumber = combinatorial(n, k);
    startingCentroids1 = (point_t **) malloc(iterationNumber * sizeof(point_t *));
    for (uint64_t i = 0; i < iterationNumber; ++i) {
        startingCentroids1[i] = (point_t *) malloc(k * sizeof(point_t));
    }
    generateSetOfStartingCentroids(startingCentroids1, dataTest1->vectors, k, n, iterationNumber);

    dataTest2 = (data_t *) malloc(sizeof(data_t));
    if (dataTest2 == NULL) return -1;
    fileForTest2 = fopen("input_binary/ex3.bin", "r");
    loadData(fileForTest2, dataTest2);

    startingCentroids2 = (point_t **) malloc(iterationNumber * sizeof(point_t *));
    for (uint64_t i = 0; i < iterationNumber; ++i) {
        startingCentroids2[i] = (point_t *) malloc(k * sizeof(point_t));
    }
    generateSetOfStartingCentroids(startingCentroids2, dataTest2->vectors, k, n, iterationNumber);

    return 0;

}

int32_t teardownGenerateStartingCentroids(void) {

    if (0 != fclose(fileForTest1)) return -1;
    for (uint64_t i = 0; i < dataTest1->size; i++) {
        free((dataTest1->vectors)[i]);
    }

    free(dataTest1->vectors);
    free(dataTest1);

    if (0 != fclose(fileForTest2)) return -1;
    for (uint64_t i = 0; i < dataTest2->size; i++) {
        free((dataTest2->vectors)[i]);
    }

    free(dataTest2->vectors);
    free(dataTest2);
    uint32_t k = 2;
    uint32_t n = 4;
    uint64_t iterationNumber = combinatorial(n, k);


    for (int i = 0; i < iterationNumber; ++i) {
        free(startingCentroids1[i]);
        free(startingCentroids2[i]);

    }
    free(startingCentroids1);
    free(startingCentroids2);


    return 0;
}

void testGenerateStartingCentroids(void) {

    //test : ex1.bin
    CU_ASSERT_EQUAL(startingCentroids1[0]->vector[0], 1);
    CU_ASSERT_EQUAL(startingCentroids1[0]->vector[1], 1);

    CU_ASSERT_EQUAL(startingCentroids1[1]->vector[0], 1);
    CU_ASSERT_EQUAL(startingCentroids1[1]->vector[1], 1);

    CU_ASSERT_EQUAL(startingCentroids1[2]->vector[0], 1);
    CU_ASSERT_EQUAL(startingCentroids1[2]->vector[1], 1);

    CU_ASSERT_EQUAL(startingCentroids1[3]->vector[0], 2);
    CU_ASSERT_EQUAL(startingCentroids1[3]->vector[1], 2);


    //test : ex3.bin
    CU_ASSERT_EQUAL(startingCentroids2[0]->vector[0], 2053);
    CU_ASSERT_EQUAL(startingCentroids2[0]->vector[1], 981);

    CU_ASSERT_EQUAL(startingCentroids2[1]->vector[0], 2053);
    CU_ASSERT_EQUAL(startingCentroids2[1]->vector[1], 981);

    CU_ASSERT_EQUAL(startingCentroids2[2]->vector[0], 2053);
    CU_ASSERT_EQUAL(startingCentroids2[2]->vector[1], 981);

    CU_ASSERT_EQUAL(startingCentroids2[3]->vector[0], 515);
    CU_ASSERT_EQUAL(startingCentroids2[3]->vector[1], 486);

}


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
         CU_add_test(generateStartingCentroidsSuite, "test to generate centroids", testGenerateStartingCentroids)) ||
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