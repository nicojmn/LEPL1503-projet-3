#include "../headers/readBinaryFileTests.h"

/** Testing input file */
FILE *readBinaryFileForTest1;
data_t *readBinaryFileDataTest1;

FILE *readBinaryFileForTest2;
data_t *readBinaryFileDataTest2;

int32_t setupBinaryFile(void) {
    readBinaryFileForTest1 = fopen("tests_files/input_binary/ex1.bin", "r");
    if (readBinaryFileForTest1 == NULL) return -1;

    readBinaryFileDataTest1 = (data_t *) malloc(sizeof(data_t));
    if (readBinaryFileDataTest1 == NULL) return -1;

    readBinaryFileForTest2 = fopen("tests_files/input_binary/ex2.bin", "r");
    if (readBinaryFileForTest2 == NULL) return -1;

    readBinaryFileDataTest2 = (data_t *) malloc(sizeof(data_t));
    if (readBinaryFileDataTest2 == NULL) return -1;
    return 0;
}

int32_t teardownBinaryFile(void) {
    if (0 != fclose(readBinaryFileForTest1)) return -1;
    for (uint64_t i = 0; i < readBinaryFileDataTest1->size; i++) {
        free((readBinaryFileDataTest1->vectors)[i]);
    }
    free(readBinaryFileDataTest1->vectors);
    free(readBinaryFileDataTest1);

    if (0 != fclose(readBinaryFileForTest2)) return -1;
    for (uint64_t i = 0; i < readBinaryFileDataTest2->size; i++) {
        free((readBinaryFileDataTest2->vectors)[i]);
    }
    free(readBinaryFileDataTest2->vectors);
    free(readBinaryFileDataTest2);
    return 0;
}

/** We've used the corresponding json file to check the correct values */
void testReadBinaryFile(void) {

    loadData(readBinaryFileForTest1, readBinaryFileDataTest1);
    CU_ASSERT_EQUAL(readBinaryFileDataTest1->dimension, 2);
    CU_ASSERT_EQUAL(readBinaryFileDataTest1->size, 7);
    CU_ASSERT_EQUAL((readBinaryFileDataTest1->vectors)[0][0], 1);
    CU_ASSERT_EQUAL((readBinaryFileDataTest1->vectors)[0][1], 1);
    CU_ASSERT_EQUAL((readBinaryFileDataTest1->vectors)[3][0], 5);
    CU_ASSERT_EQUAL((readBinaryFileDataTest1->vectors)[3][1], 7);
    CU_ASSERT_EQUAL((readBinaryFileDataTest1->vectors)[6][0], 4);
    CU_ASSERT_EQUAL((readBinaryFileDataTest1->vectors)[6][1], 5);

    loadData(readBinaryFileForTest2, readBinaryFileDataTest2);
    CU_ASSERT_EQUAL(readBinaryFileDataTest2->dimension, 2);
    CU_ASSERT_EQUAL(readBinaryFileDataTest2->size, 13);
    CU_ASSERT_EQUAL((readBinaryFileDataTest2->vectors)[0][0], 1);
    CU_ASSERT_EQUAL((readBinaryFileDataTest2->vectors)[0][1], 1);
    CU_ASSERT_EQUAL((readBinaryFileDataTest2->vectors)[12][0], 2);
    CU_ASSERT_EQUAL((readBinaryFileDataTest2->vectors)[12][1], 1);
}