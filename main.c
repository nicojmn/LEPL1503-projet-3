#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>

#include "headers/distance.h"
#include "headers/kMeans.h"
#include "headers/generateStartingCentroids.h"
#include "headers/readBinaryFile.h"
#include "headers/writeOutputFile.h"
#include "headers/manageArgs.h"
#include "headers/manageHeap.h"

// inputs of the program
args_t programArguments;

// storage of the points collected from the input binary file
data_t *generalData;

// general features of the kMeans problem
point_t **startingCentroids;
uint32_t kCentroids;
uint64_t iterationNumber;
squared_distance_func_t generic_func;

// Threads
#define N 2 // size of the buffer
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
buffer_t *buffer;

/**
 * @param indexes: an array containing the starting index (included) and the end (excluded)
 * The function calculates a kMeans problem, one by one from [start: end[ and put it on the buffer
 * each time the calculus is done
 */
void *produce(void *indexes) {
    for (uint32_t i = ((uint32_t *) indexes)[0]; i < ((uint32_t *) indexes)[1]; ++i) {
        kMeans_t *kMeansSimulation = createOneInstance(generalData->vectors, startingCentroids, i, kCentroids,
                                                       generalData->size, generalData->dimension);
        runKMeans(kMeansSimulation,
                  (squared_distance_func_t (*)(const point_t *, const point_t *, uint32_t)) generic_func);
        point_t **clusters = generateClusters(kMeansSimulation, programArguments.quiet);
        uint64_t distortionValue = distortion(kMeansSimulation,
                                              (squared_distance_func_t (*)(const point_t *, const point_t *,
                                                                           uint32_t)) generic_func);
        sem_wait(&empty);
        if (pthread_mutex_lock(&mutex) != 0) return (void *) -1;
        (buffer->kMeansInstances)[buffer->head] = kMeansSimulation;
        (buffer->clustersOfInstances)[buffer->head] = clusters;
        (buffer->distortionValues)[buffer->head] = distortionValue;
        (buffer->indexes)[buffer->head] = i;
        buffer->head = (buffer->head + 1) % N;
        if (pthread_mutex_unlock(&mutex) != 0) return (void *) -1;
        sem_post(&full);
    }
    return NULL;
}

/**
 * It writes each kMeans available on the buffer in the output csv file
 */
void *consume() {
    uint64_t *nbOfElemToConsume = malloc(sizeof(uint64_t));
    if (nbOfElemToConsume == NULL) return NULL;
    *nbOfElemToConsume = iterationNumber;
    while (*nbOfElemToConsume > 0) {
        sem_wait(&full);
        if (pthread_mutex_lock(&mutex) != 0) return (void *) -1;
        uint32_t i = (buffer->indexes)[buffer->tail];
        kMeans_t *kMeansSimulation = (buffer->kMeansInstances)[buffer->tail];
        point_t **clusters = (buffer->clustersOfInstances)[buffer->tail];
        uint64_t distortionValue = (buffer->distortionValues)[buffer->tail];
        if (writeOneKMeans(kMeansSimulation, programArguments.quiet, programArguments.output_stream,
                           startingCentroids[i], clusters, distortionValue) == -1) {
            clean(kMeansSimulation);
            fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
            return (void *) -1;
        }
        buffer->tail = (buffer->tail + 1) % N;
        clean(kMeansSimulation);
        if (pthread_mutex_unlock(&mutex) != 0) return (void *) -1;
        sem_post(&empty);
        (*nbOfElemToConsume)--;
    }
    if (fprintf(programArguments.output_stream, "\n") < 0) return (void *) -1;
    free(nbOfElemToConsume);
    return NULL;
}

int main(int argc, char *argv[]) {

    // Collect the arguments and put them in programArguments
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

    // Generate all the starting centroids necessary
    // The time took by the function generateSetOfStartingCentroids is negligible (no need to allocate a thread)
    startingCentroids = (point_t **) malloc(iterationNumber * sizeof(point_t *));
    if (generateSetOfStartingCentroids(startingCentroids, generalData->vectors, kCentroids, nFirstPoints,
                                       iterationNumber) == -1) {
        fullClean(generalData, NULL, iterationNumber, programArguments, NULL);
        return -1;
    }

    // Write the headlines in the output csv file
    if (writeHeadline(programArguments.quiet, programArguments.output_stream) == -1) {
        fullClean(generalData, startingCentroids, iterationNumber, programArguments, NULL);
        return -1;
    }

    // Setup of the threads
    buffer = createBuffer((uint8_t) N);
    if (buffer == NULL || pthread_mutex_init(&mutex, NULL) != 0 ||
        sem_init(&empty, 0, N) != 0 || sem_init(&full, 0, 0) != 0) {
        fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
        return -1;
    }

    pthread_t producerThreads[nThreads - 1]; // nThreads-1 because the main thread is a producer too
    pthread_t consumerThread;

    uint32_t amountOfInstancePerThread = (uint32_t) iterationNumber / nThreads;
    uint16_t rest = (uint16_t) iterationNumber % nThreads;
    uint32_t start = 0;
    uint32_t end = amountOfInstancePerThread;
    uint32_t listOfIndexes[nThreads][2];

    // Launch of the threads
    for (int i = 0; i < nThreads; i++) {
        // The last producer thread is our main thread
        if (i == nThreads - 1) {
            // Launch the consumer
            if (pthread_create(&consumerThread, NULL, &consume, NULL) != 0) {
                fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
                return -1;
            }
            listOfIndexes[i][0] = start;
            listOfIndexes[i][1] = end;
            if (produce((void *) listOfIndexes[i]) == (void *) -1) {
                fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
                return -1;
            }
        } else {
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
    }

    // Closing the threads
    for (uint32_t i = 0; i < nThreads - 1; i++) {
        if (pthread_join(producerThreads[i], NULL) != 0) {
            fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
            return -1;
        }
    }
    if (pthread_join(consumerThread, NULL) != 0) {
        fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
        return -1;
    }

    // Closing, freeing, destroying what is necessary
    fullClean(generalData, startingCentroids, iterationNumber, programArguments, buffer);
    if (pthread_mutex_destroy(&mutex) != 0) return -1;

    if (!programArguments.test_mode) {
        printf("The job is done !\n");
    }
    return 0;
}