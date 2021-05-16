#ifndef READBINARYFILETESTS_H
#define READBINARYFILETESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/readBinaryFile.h"

/**
 * Function to prepare tests (malloc(), assigning variables)
 * @return 0 if everything goes well, -1 if an error occurs
 */
int32_t setupBinaryFile(void);

/**
 * Function to clean memory after tests
 * @return 0
 */
int32_t teardownBinaryFile(void);

void testReadBinaryFile(void);

#endif
