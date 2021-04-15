#include "../headers/manageHeap.h"

void clean(k_means_t *kMeans) {
    for (int i = 0; i < kMeans->k; ++i) {
        free((kMeans->centroids)[i].vector);
    }
    free(kMeans->centroids);
    free(kMeans->clustersSize);
    free(kMeans->points);
    // Vectors of points are intentionally not freed
    free(kMeans);
}

void fullClean(data_t *generalData, point_t **startingCentroids, uint64_t iterationNumber, args_t args) {
    for (uint64_t i = 0; i < generalData->size; ++i) {
        free(generalData->vectors[i]);
    }
    free(generalData->vectors);
    free(generalData);
    for (uint64_t i = 0; i < iterationNumber; ++i) {
        free(startingCentroids[i]);
    }
    free(startingCentroids);

    // close the files opened by parse_args
    if (args.input_stream != stdin) {
        fclose(args.input_stream);
    }
    if (args.output_stream != stdout) {
        fclose(args.output_stream);
    }
}