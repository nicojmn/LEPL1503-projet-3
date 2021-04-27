#ifndef DISTORTION_H
#define DISTORTION_H

#include <stdint.h>
#include "kmeansStruct.h"
#include "distance.h"

uint64_t distortion(kMeans_t *kMeans, squared_distance_func_t
distanceFunction(const point_t *p1, const point_t *p2, uint32_t dimension));

#endif
