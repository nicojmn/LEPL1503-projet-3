#include "../headers/generateStartingCentroids.h"

uint64_t factorial(uint32_t x) {
    uint64_t result = 1;
    while (x > 1) {
        result *= x;
        x--;
    }
    return result;
}

uint64_t combinatorial(uint32_t n, uint32_t k) {
    uint64_t denominator1 = k;
    uint64_t denominator2 = n - k;
    uint64_t result = 1;
    if (denominator1 > denominator2) {
        uint32_t iterationNbr = n - denominator1;
        while (iterationNbr > 0) {
            result *= n;
            n--;
            iterationNbr--;
        }
        return result / factorial(denominator2);
    } else {
        uint32_t iterationNbr = n - denominator2;
        while (iterationNbr > 0) {
            result *= n;
            n--;
            iterationNbr--;
        }
        return result / factorial(denominator1);
    }
}

void generateSetOfStartingCentroids(point_t **startingCentroidsID, int64_t **vectors,
                                    uint32_t k, uint32_t n, uint64_t iterationNbr) {

    int32_t indices[k];

    // First set of centroids
    for (int i = 0; i < k; ++i) {
        indices[i] = i;
    }

    for (int i = 0; i < iterationNbr; ++i) {
        // Creating the set of centroids
        for (int l = 0; l < k; ++l) {
            startingCentroidsID[i][l].vector = vectors[indices[l]];
        }
        int j = k - 1;
        while (indices[j] == n - 1 || indices[j] == indices[j + 1] - 1) {
            j--;
        }
        indices[j]++;
        for (int l = j + 1; l < k; ++l) {
            indices[l] = indices[l - 1] + 1;
        }
    }
}