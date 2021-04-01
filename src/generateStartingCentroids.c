#include "../headers/generateStartingCentroids.h"

int64_t factorial(int64_t x) {
    int64_t result = 1;
    while (x > 1) {
        result *= x;
        x--;
    }
    return result;
}


void generate(point_t **startingCentroidsID, int64_t **vectors, int32_t k, int32_t n) {

}