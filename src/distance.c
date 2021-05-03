#include "../headers/distance.h"


uint64_t absVal(int64_t x) {
    if (x < 0) return (uint64_t) -x;
    return (uint64_t) x;
}

uint64_t squared_manhattan_distance(const point_t *p1, const point_t *p2, uint32_t dimension) {
    uint64_t result = 0;
    for (uint32_t i = 0; i < dimension; ++i) {
        result += absVal(p1->vector[i] - p2->vector[i]);
    }
    return result * result;
}


uint64_t squared_euclidean_distance(const point_t *p1, const point_t *p2, uint32_t dimension) {
    uint64_t result = 0;
    for (uint32_t i = 0; i < dimension; ++i) {
        result += (p1->vector[i] - p2->vector[i]) * (p1->vector[i] - p2->vector[i]);
    }
    return result;
}

