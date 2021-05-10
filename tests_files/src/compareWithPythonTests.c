#include "../headers/compareWithPythonTests.h"


int32_t compareWithPythonSetup(void) {
    return 0;
}

int32_t compareWithPythonTeardown(void) {
    return 0;
}

void testCompare(void) {
    printf("\n");
    char *command = "sh tests_files/bash/compareWithPythonTests.sh";
    system(command);
}

