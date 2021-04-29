#ifndef READBINARYFILETESTS_H
#define READBINARYFILETESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/readBinaryFile.h"

int32_t setupBinaryFile(void);

int32_t teardownBinaryFile(void);

void testReadBinaryFile(void);

#endif
