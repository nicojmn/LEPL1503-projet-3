
#include "../headers/distance.h"

int64_t absVal(int64_t x) {
    if (x < 0) return (int64_t) - x;
    return (int64_t) x;
}

int64_t squared_manhattan_distance(const point_t *p1, const point_t *p2, int32_t dimension) {
    int64_t result = 0;
    for (int i = 0; i < dimension; ++i) {
        result += absVal(p1->vector[i] - p2->vector[i]);
    }
    return result * result;
}


int64_t squared_euclidean_distance(const point_t *p1, const point_t *p2, int32_t dimension) {
    int64_t result = 0;
    for (int i = 0; i < dimension; ++i) {
        result += (p1->vector[i] - p2->vector[i]) * (p1->vector[i] - p2->vector[i]);
    }
    return result;
}

