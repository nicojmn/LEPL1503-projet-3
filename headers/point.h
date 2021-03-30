
#ifndef POINT_H
#define POINT_H

#include <stdint.h>

typedef struct point {
    int64_t *vector;
    struct point *next;
} point_t;

#endif //POINT_H
