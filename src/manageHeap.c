#include "../headers/manageHeap.h"

buffer_t *createBuffer(uint8_t bufferSize) {
    buffer_t *buffer = malloc(sizeof(buffer_t));
    if (buffer == NULL) return NULL;
    buffer->kMeansInstances = malloc(bufferSize * sizeof(kMeans_t *));
    if (buffer->kMeansInstances == NULL) return NULL;
    buffer->clustersOfInstances = malloc(bufferSize * sizeof(point_t **));
    if (buffer->clustersOfInstances == NULL) return NULL;
    buffer->distortionValues = malloc(bufferSize * sizeof(int64_t));
    if (buffer->distortionValues == NULL) return NULL;
    buffer->indexes = malloc(bufferSize * sizeof(uint32_t));
    if (buffer->indexes == NULL) return NULL;
    buffer->head = 0;
    buffer->tail = 0;
    return buffer;
}

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
    // Freeing the buffer
    if (buffer != NULL) {
        free(buffer->kMeansInstances);
        free(buffer->clustersOfInstances);
        free(buffer->distortionValues);
        free(buffer->indexes);
        free(buffer);
    }
}