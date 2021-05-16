#include "../headers/manageHeap.h"

void clean(kMeans_t *kMeans) {
    for (uint32_t i = 0; i < kMeans->k; ++i) {
        free((kMeans->centroids)[i].vector);
    }
    free(kMeans->centroids);
    free(kMeans->clustersSize);
    free(kMeans->points);
    // Vectors of points are intentionally not freed
    free(kMeans);
}

void fullClean(data_t *generalData, point_t **startingCentroids, uint64_t iterationNumber,
               args_t args, buffer_t *buffer) {

    // Freeing the data collected from the input file
    for (uint64_t i = 0; i < generalData->size; ++i) {
        free(generalData->vectors[i]);
    }
    free(generalData->vectors);
    free(generalData);

    // Freeing the set of starting centroids
    if (startingCentroids != NULL) {
        for (uint64_t i = 0; i < iterationNumber; ++i) {
            free(startingCentroids[i]);
        }
        free(startingCentroids);
    }

    // Close the files opened by parse_args
    if (args.input_stream != stdin) {
        fclose(args.input_stream);
    }
    if (args.output_stream != stdout) {
        fclose(args.output_stream);
    }
    // Freeing the buffer
    if (buffer != NULL) {
        free(buffer->kMeansInstances);
        free(buffer->clustersOfInstances);
        free(buffer->distortionValues);
        free(buffer->indexes);
        free(buffer);
    }
}