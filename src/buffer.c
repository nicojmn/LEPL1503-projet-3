#include "../headers/buffer.h"

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
