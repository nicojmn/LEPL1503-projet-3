
#ifndef POINT_H
#define POINT_H

#include <stdint.h>

typedef struct point {
    int64_t *vector;
    int32_t nearestCentroidID;
} point_t;

#endif
