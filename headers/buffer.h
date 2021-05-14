#ifndef BUFFER_H
#define BUFFER_H

#include "kMeans.h"

/** Structure use by the producer threads and consumer thread to communicate */
typedef struct {
    kMeans_t **kMeansInstances;
    uint64_t *distortionValues;
    point_t ***clustersOfInstances;
    uint32_t *indexes;
    uint8_t head; // free place
    uint8_t tail; // oldest input
} buffer_t;

/**
 * @param bufferSize (because we only have one consumer thread, it's useless to create a large buffer)
 * @return the buffer used by our threads in the producer/consumer process
 */
buffer_t *createBuffer(uint32_t bufferSize);

#endif //BUFFER_H
