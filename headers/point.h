
#ifndef POINT_H
#define POINT_H

#include <stdint.h>

typedef struct {
    int64_t *vector;
    int32_t dimension;
} point_t;

#endif //POINT_H
