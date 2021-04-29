#include "../headers/tests.h"


int main() {

    CU_pSuite distanceTestSuite = NULL;
    CU_pSuite distortionTestSuite = NULL;
    CU_pSuite updateCentroidsTestSuite = NULL;
    CU_pSuite assignVectorSuite = NULL;
    CU_pSuite kMeansSuite = NULL;
    CU_pSuite binaryFileSuite = NULL;
    CU_pSuite csvFileSuite = NULL;
    CU_pSuite generateStartingCentroidsSuite = NULL;

    /** initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    /** add a suite to the registry */
    distanceTestSuite = CU_add_suite("distance tests_files", distanceSetup, distanceTeardown);
    distortionTestSuite = CU_add_suite("distortion test", distortionSetup, distortionTeardown);
    generateStartingCentroidsSuite = CU_add_suite("generateStartingCentroids test", setupGenerateStartingCentroids,
                                                  teardownGenerateStartingCentroids);
    updateCentroidsTestSuite = CU_add_suite("updateCentroids test", updateCentroidsSetup, updateCentroidsTeardown);
    assignVectorSuite = CU_add_suite("Assign vector", assignVectorSetup, assignVectorTeardown);
    kMeansSuite = CU_add_suite("kMeans test", kMeansSetup, kMeansTeardown);
    binaryFileSuite = CU_add_suite("binary file loading test", setupBinaryFile, teardownBinaryFile);
    csvFileSuite = CU_add_suite("writing into csv file", setupCreateOutputFile, teardownCreateOutputFile);

    if (distanceTestSuite == NULL || distortionTestSuite == NULL ||
        updateCentroidsTestSuite == NULL || assignVectorSuite == NULL || kMeansSuite == NULL
        || binaryFileSuite == NULL || csvFileSuite == NULL || generateStartingCentroidsSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** add the tests_files to the suite */
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
        (NULL == CU_add_test(kMeansSuite, "One iteration of Kmeans", testKMeansDimension2)) ||
        (NULL == CU_add_test(binaryFileSuite, "Test of loadingData", testReadBinaryFile)) ||
        (NULL == CU_add_test(csvFileSuite, "test of writing into csv", test_createOutputFileDimension2))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /** Run all tests_files using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}