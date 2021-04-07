#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/CUError.h>
#include <CUnit/TestDB.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>


#include "../headers/readBinaryFileTests.h"

int32_t setupBinaryFile(void) {
    fileForTest1 = fopen("input_binary/ex1.bin", "r");
    if (fileForTest1 == NULL) return -1;

    dataTest1 = (data_t *) malloc(sizeof(data_t));
    if (dataTest1 == NULL) return -1;

    fileForTest2 = fopen("input_binary/ex2.bin", "r");
    if (fileForTest2 == NULL) return -1;

    dataTest2 = (data_t *) malloc(sizeof(data_t));
    if (dataTest2 == NULL) return -1;
    return 0;
}

int32_t teardownBinaryFile(void) {
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
    return 0;
}

void testReadBinaryFile(void) {

    loadData(fileForTest1, dataTest1);
    CU_ASSERT_EQUAL(dataTest1->dimension, 2);
    CU_ASSERT_EQUAL(dataTest1->size, 7);
    CU_ASSERT_EQUAL((dataTest1->vectors)[0][0], 1);
    CU_ASSERT_EQUAL((dataTest1->vectors)[0][1], 1);
    CU_ASSERT_EQUAL((dataTest1->vectors)[3][0], 5);
    CU_ASSERT_EQUAL((dataTest1->vectors)[3][1], 7);
    CU_ASSERT_EQUAL((dataTest1->vectors)[6][0], 4);
    CU_ASSERT_EQUAL((dataTest1->vectors)[6][1], 5);

    loadData(fileForTest2, dataTest2);
    CU_ASSERT_EQUAL(dataTest2->dimension, 2);
    CU_ASSERT_EQUAL(dataTest2->size, 13);
    CU_ASSERT_EQUAL((dataTest2->vectors)[0][0], 1);
    CU_ASSERT_EQUAL((dataTest2->vectors)[0][1], 1);
    CU_ASSERT_EQUAL((dataTest2->vectors)[12][0], 2);
    CU_ASSERT_EQUAL((dataTest2->vectors)[12][1], 1);
}