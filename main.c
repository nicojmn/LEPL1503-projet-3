#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "headers/distance.h"
#include "headers/kMeans.h"
#include "headers/generateStartingCentroids.h"
#include "headers/readBinaryFile.h"
#include "headers/writeOutputFile.h"
#include "headers/manageArgs.h"
#include "headers/manageHeap.h"
#include "headers/buffer.h"

// Inputs of the program
args_t programArguments;

// Storage of the points collected from the input binary file
data_t *generalData;

// General features of the kMeans problem
point_t **startingCentroids;
uint32_t kCentroids;
uint64_t iterationNumber;
squared_distance_func_t generic_func;

// Threads
uint32_t bufferSize;
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
buffer_t *buffer;

/**
 * @param indexes: an array containing the starting index (included) and the ending index (excluded)
 * The function calculates a kMeans problem, one by one [start: end[ and put it on the buffer
 * each time a kMeans problem has been calculated
 */
void *produce(void *indexes) {
    for (uint32_t i = ((uint32_t *) indexes)[0]; i < ((uint32_t *) indexes)[1]; ++i) {
        // Calculation of a kMeans problem
        kMeans_t *kMeansSimulation = createOneInstance(generalData->vectors, startingCentroids, i, kCentroids,
                                                       generalData->size, generalData->dimension);
        runKMeans(kMeansSimulation,
                  (squared_distance_func_t (*)(const point_t *, const point_t *, uint32_t)) generic_func);
        point_t **clusters = generateClusters(kMeansSimulation, programArguments.quiet);
        uint64_t distortionValue = distortion(kMeansSimulation,
                                              (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                           uint32_t)) generic_func);
        // Waits for space on the buffer then put the result on the buffer
        sem_wait(&empty);
        if (pthread_mutex_lock(&mutex) != 0) return (void *) -1;
        (buffer->kMeansInstances)[buffer->head] = kMeansSimulation;
        (buffer->clustersOfInstances)[buffer->head] = clusters;
        (buffer->distortionValues)[buffer->head] = distortionValue;
        (buffer->indexes)[buffer->head] = i;
        buffer->head = (buffer->head + 1) % bufferSize;
        if (pthread_mutex_unlock(&mutex) != 0) return (void *) -1;
        sem_post(&full);
    }
    return NULL;
}

/** It writes each kMeans result available on the buffer into the output csv file */
void *consume() {
    uint64_t *nbOfElemToConsume = malloc(sizeof(uint64_t));
    if (nbOfElemToConsume == NULL) return NULL;
    *nbOfElemToConsume = iterationNumber;

    kMeans_t **kMeansSimulation = malloc(sizeof(kMeans_t *));
    point_t ***clusters = malloc(sizeof(point_t **));
    if (kMeansSimulation == NULL || clusters == NULL) return (void *) -1;

    while (*nbOfElemToConsume > 0) {
        // Waits for a kMeans problem available on the buffer then take it
        sem_wait(&full);
        if (pthread_mutex_lock(&mutex) != 0) return (void *) -1;
        uint32_t i = (buffer->indexes)[buffer->tail];
        *kMeansSimulation = (buffer->kMeansInstances)[buffer->tail];
        *clusters = (buffer->clustersOfInstances)[buffer->tail];
        uint64_t distortionValue = (buffer->distortionValues)[buffer->tail];
        buffer->tail = (buffer->tail + 1) % bufferSize;
        if (pthread_mutex_unlock(&mutex) != 0) return (void *) -1;
        sem_post(&empty);

        // Writes the kMeans problem into the csv file
        if (writeOneKMeans(*kMeansSimulation, programArguments.quiet, programArguments.output_stream,
                           startingCentroids[i], *clusters, distortionValue) == -1) {
            clean(*kMeansSimulation);
            fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
            return (void *) -1;
        }
        clean(*kMeansSimulation);
        (*nbOfElemToConsume)--;
    }
    if (fprintf(programArguments.output_stream, "\n") < 0) return (void *) -1;
    free(nbOfElemToConsume);
    free(kMeansSimulation);
    free(clusters);
    return NULL;
}

int main(int argc, char *argv[]) {

    // Collect the arguments and put them into programArguments
    parse_args(&programArguments, argc, argv);

    // Check if kCentroids <= nFirstPoints
    if (verifyArguments(programArguments) == -1) return -1;

    // Display the current options
    displayOptions(programArguments);

    // Collect data from the input binary file
    generalData = (data_t *) malloc(sizeof(data_t));
    if (generalData == NULL) return -1;
    if (loadData(programArguments.input_stream, generalData) == -1) return -1;

    // General features of the kMeans problem
    generic_func = programArguments.squared_distance_func;
    kCentroids = programArguments.k;
    uint32_t nFirstPoints = programArguments.n_first_initialization_points;
    // We take the minimum between n_first_initialization_points and the number of points
    if (generalData->size < nFirstPoints) {
        nFirstPoints = generalData->size;
    }
    uint32_t nThreads = programArguments.n_threads;
    iterationNumber = combinatorial(nFirstPoints, kCentroids);

    // Generate all necessary starting centroids
    // The time took by the function generateSetOfStartingCentroids is negligible (no need to allocate a thread)
    startingCentroids = (point_t **) malloc(iterationNumber * sizeof(point_t *));
    if (startingCentroids == NULL || generateSetOfStartingCentroids(startingCentroids, generalData->vectors,
                                                                    kCentroids, nFirstPoints, iterationNumber) == -1) {
        fullClean(generalData, NULL, iterationNumber, programArguments, NULL);
        return -1;
    }

    // Write the headlines into the output csv file
    if (writeHeadline(programArguments.quiet, programArguments.output_stream) == -1) {
        fullClean(generalData, startingCentroids, iterationNumber, programArguments, NULL);
        return -1;
    }

    // Setup of the threads
    bufferSize = nThreads;
    buffer = createBuffer(bufferSize);
    if (buffer == NULL || pthread_mutex_init(&mutex, NULL) != 0 ||
        sem_init(&empty, 0, bufferSize) != 0 || sem_init(&full, 0, 0) != 0) {
        fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
        return -1;
    }

    pthread_t producerThreads[nThreads];

    uint32_t amountOfInstancePerThread = (uint32_t) iterationNumber / nThreads;
    uint16_t rest = (uint16_t) iterationNumber % nThreads;
    uint32_t start = 0;
    uint32_t end = amountOfInstancePerThread;
    uint32_t listOfIndexes[nThreads][2];

    // Launch of the producer threads
    for (int i = 0; i < nThreads; i++) {
        // Allocate fairly the integer division rest to each producer (17//3 -> 6 6 5)
        if (rest > 0) {
            end++;
            rest--;
        }
        listOfIndexes[i][0] = start;
        listOfIndexes[i][1] = end;
        if (pthread_create(&producerThreads[i], NULL, &produce, (void *) listOfIndexes[i]) != 0) {
            fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
            return -1;
        }
        start = end;
        end += amountOfInstancePerThread;
    }
    // Launch the consumer thread which is the main thread
    if (consume() == (void *) -1) {
        fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
        return -1;
    }

    // Closing the producer threads
    for (uint32_t i = 0; i < nThreads; i++) {
        if (pthread_join(producerThreads[i], NULL) != 0) {
            fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
            return -1;
        }
    }

    // Closing, freeing, destroying what is necessary
    fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
    if (pthread_mutex_destroy(&mutex) != 0) return -1;

    if (!programArguments.test_mode) {
        printf("The job is done !\n");
    }
    return 0;
}