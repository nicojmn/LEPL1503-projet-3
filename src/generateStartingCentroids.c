#include "../headers/generateStartingCentroids.h"

int64_t factorial(int64_t x) {
    int64_t result = 1;
    while (x > 1) {
        result *= x;
        x--;
    }
    return result;
}

void generateSetOfStartingCentroids(point_t **startingCentroidsID, int64_t **vectors,
                                    int32_t k, int32_t n, int32_t iterationNbr) {

    int32_t indices[k];

    // First set of centroids
    for (int i = 0; i < k; ++i) {
        indices[i] = i;
    }

    for (int i = 0; i < iterationNbr; ++i) {
        // Creating the set of centroids
        for (int j = 0; j < k; ++j) {
            startingCentroidsID[i][j].vector = vectors[indices[j]];
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