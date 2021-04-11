#ifndef PROJET_CMAKE_READBINARYFILETESTS_H
#define PROJET_CMAKE_READBINARYFILETESTS_H

#include "../../headers/readBinaryFile.h"

/** Testing input file */
FILE *fileForTest1;
data_t *dataTest1;
FILE *fileForTest2;
data_t *dataTest2;

int32_t setupBinaryFile(void);

int32_t teardownBinaryFile(void);

void testReadBinaryFile(void);

#endif
