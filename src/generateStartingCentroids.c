#include "../headers/generateStartingCentroids.h"

uint64_t factorial(uint64_t x) {
    uint64_t result = 1;
    while (x > 1) {
        result *= x;
        x--;
    }
    return result;
}

uint64_t combinatorial(uint32_t nFirstPoints, uint32_t kCentroids) {
    uint64_t denominator1 = kCentroids;
    uint64_t denominator2 = nFirstPoints - kCentroids;
    uint64_t result = 1;
    // We avoid unnecessary calculus : (5!)/(3!*2!) = (5*4)/(2!)
    if (denominator1 > denominator2) {
        uint32_t iterationNbr = nFirstPoints - denominator1;
        while (iterationNbr > 0) {
            result *= nFirstPoints;
            nFirstPoints--;
            iterationNbr--;
        }
        return result / factorial(denominator2);
    } else {
        uint32_t iterationNbr = nFirstPoints - denominator2;
        while (iterationNbr > 0) {
            result *= nFirstPoints;
            nFirstPoints--;
            iterationNbr--;
        }
        return result / factorial(denominator1);
    }
}

int32_t generateSetOfStartingCentroids(point_t **startingCentroids, int64_t **vectors,
                                       uint32_t kCentroids, uint32_t nFirstPoints, uint64_t iterationNumber) {

    for (uint64_t i = 0; i < iterationNumber; ++i) {
        startingCentroids[i] = (point_t *) malloc(kCentroids * sizeof(point_t));
        if (startingCentroids[i] == NULL) return -1;
    }

    uint32_t indices[kCentroids];

    // First set of centroids
    for (uint32_t i = 0; i < kCentroids; ++i) {
        indices[i] = i;
    }

    for (uint64_t i = 0; i < iterationNumber; ++i) {
        // Creating the set of centroids for each iteration i
        for (uint32_t l = 0; l < kCentroids; ++l) {
            startingCentroids[i][l].vector = vectors[indices[l]];
        }
        // j can become negative so no uint32_t are allowed here
        int32_t j = (int32_t) kCentroids - 1;
        while (j > -1 && (indices[j] == nFirstPoints - 1 ||
                          (j + 1 < kCentroids && indices[j] == indices[j + 1] - 1))) {
            j--;
        }
        indices[j]++;
        // the operation m - 1 can occur so m must be int32_t
        for (int32_t m = (j + 1); m < kCentroids; ++m) {
            indices[m] = indices[m - 1] + 1;
        }
    }
    return 0;
}