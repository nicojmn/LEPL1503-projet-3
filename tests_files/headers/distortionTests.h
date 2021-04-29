#ifndef DISTORTIONTESTS_H
#define DISTORTIONTESTS_H

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../headers/kMeans.h"


void testDistortion(void);

int32_t distortionSetup(void);

int32_t distortionTeardown(void);

#endif
