#include "../headers/compareWithPythonTests.h"


int32_t compareWithPythonSetup(void) {
    return 0;
}

int32_t compareWithPythonTeardown(void) {
    return 0;
}

void testCompare(void) {
    printf("\n");

    // The comparisons are handled with the bash file compareWithPythonTests.sh
    char *command = "sh tests_files/bash/compareWithPythonTests.sh";
    system(command);

    FILE *resultFile = fopen("tests_files/comparisonResult.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(resultFile);

    char result[8];
    fgets(result, sizeof(result), resultFile);
    char *expected = "SUCCESS\0";

    // We check if the comparisons went on well
    CU_ASSERT_STRING_EQUAL(result, expected);

    fclose(resultFile);
}

