#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/generateCentroidsTests.h"


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

