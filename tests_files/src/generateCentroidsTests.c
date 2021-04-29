#include "../headers/generateCentroidsTests.h"


point_t **startingCentroids1;
point_t **startingCentroids2;

data_t *dataTest1;
FILE *fileForTest1;

data_t *dataTest2;
FILE *fileForTest2;

int32_t setupGenerateStartingCentroids(void) {

    dataTest1 = (data_t *) malloc(sizeof(data_t));
    if (dataTest1 == NULL) return -1;
    fileForTest1 = fopen("tests_files/input_binary/ex1.bin", "r");
    loadData(fileForTest1, dataTest1);

    uint32_t k = 2;
    uint32_t n = 4;

    uint64_t iterationNumber = combinatorial(n, k);

    startingCentroids1 = (point_t **) malloc(iterationNumber * sizeof(point_t *));
    generateSetOfStartingCentroids(startingCentroids1, dataTest1->vectors, k, n, iterationNumber);

    dataTest2 = (data_t *) malloc(sizeof(data_t));
    if (dataTest2 == NULL) return -1;
    fileForTest2 = fopen("tests_files/input_binary/ex3.bin", "r");
    loadData(fileForTest2, dataTest2);

    startingCentroids2 = (point_t **) malloc(iterationNumber * sizeof(point_t *));
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

/** We've used the corresponding python function to get the correct value */
void testGenerateStartingCentroids(void) {

    // using ex1.bin
    CU_ASSERT_EQUAL(startingCentroids1[0]->vector[0], 1);
    CU_ASSERT_EQUAL(startingCentroids1[0]->vector[1], 1);

    CU_ASSERT_EQUAL(startingCentroids1[1]->vector[0], 1);
    CU_ASSERT_EQUAL(startingCentroids1[1]->vector[1], 1);

    CU_ASSERT_EQUAL(startingCentroids1[2]->vector[0], 1);
    CU_ASSERT_EQUAL(startingCentroids1[2]->vector[1], 1);

    CU_ASSERT_EQUAL(startingCentroids1[3]->vector[0], 2);
    CU_ASSERT_EQUAL(startingCentroids1[3]->vector[1], 2);


    // using ex3.bin
    CU_ASSERT_EQUAL(startingCentroids2[0]->vector[0], 2053);
    CU_ASSERT_EQUAL(startingCentroids2[0]->vector[1], 981);

    CU_ASSERT_EQUAL(startingCentroids2[1]->vector[0], 2053);
    CU_ASSERT_EQUAL(startingCentroids2[1]->vector[1], 981);

    CU_ASSERT_EQUAL(startingCentroids2[2]->vector[0], 2053);
    CU_ASSERT_EQUAL(startingCentroids2[2]->vector[1], 981);

    CU_ASSERT_EQUAL(startingCentroids2[3]->vector[0], 515);
    CU_ASSERT_EQUAL(startingCentroids2[3]->vector[1], 486);
}

void testCombinatorial() {

    // (1!) / (1!0!) = 1
    CU_ASSERT_EQUAL(combinatorial(1, 1), 1);

    // (3!) / (2!1!) = 3
    CU_ASSERT_EQUAL(combinatorial(3, 2), 3);

    // (10!) / (7!3!) = (10*9*8) / (3 * 2) = 120
    CU_ASSERT_EQUAL(combinatorial(10, 7), 120);

    // (200!) / (198!2!) = (200*199) / (2) = 19900
    CU_ASSERT_EQUAL(combinatorial(200, 198), 19900);
}
