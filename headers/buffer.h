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
 * @param bufferSize: the size of the buffer which equal the number of producer thread
 * @return the buffer used by our threads during the producers-consumers process
 */
buffer_t *createBuffer(uint32_t bufferSize);

#endif //BUFFER_H
