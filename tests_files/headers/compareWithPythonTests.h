#ifndef COMPAREWITHPYTHONTESTS_H
#define COMPAREWITHPYTHONTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

int32_t compareWithPythonSetup(void);

int32_t compareWithPythonTeardown(void);

void testCompare(void);

#endif // COMPAREWITHPYTHONTESTS_H
