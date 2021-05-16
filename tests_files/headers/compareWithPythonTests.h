#ifndef COMPAREWITHPYTHONTESTS_H
#define COMPAREWITHPYTHONTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Function to prepare tests (malloc(), assigning variables)
 * @return 0 if everything goes well, -1 if an error occurs
 */
int32_t compareWithPythonSetup(void);

/**
 * Function to clean memory after tests
 * @return
 */
int32_t compareWithPythonTeardown(void);

/**
 * Compare C solution with python solution
 */
void testCompare(void);

#endif // COMPAREWITHPYTHONTESTS_H
