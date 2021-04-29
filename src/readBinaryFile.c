#include "../headers/readBinaryFile.h"


int32_t loadData(FILE *inputFile, data_t *generalData) {

    // We retrieve the dimension
    uint32_t *dimension = (uint32_t *) malloc(sizeof(uint32_t));
    if (dimension == NULL) return -1;
    fread(dimension, 4 * sizeof(char), 1, inputFile);
    generalData->dimension = (uint32_t) be32toh(*dimension);

    // We retrieve the size (number of points)
    if (fseek(inputFile, 4, SEEK_SET) == -1) return -1;
    uint64_t *size = (uint64_t *) malloc(sizeof(uint64_t));
    if (size == NULL) return -1;
    fread(size, 8 * sizeof(char), 1, inputFile);
    generalData->size = (uint64_t) be64toh(*size);

    // We retrieve all the points
    if (fseek(inputFile, 12, SEEK_SET) == -1) return -1;
    int64_t *buffer = (int64_t *) malloc((generalData->dimension) * (generalData->size) * sizeof(int64_t));
    if (buffer == NULL) return -1;

    fread(buffer, 8 * sizeof(char), (generalData->dimension) * (generalData->size), inputFile);

    generalData->vectors = (int64_t **) malloc(generalData->size * sizeof(int64_t * ));
    for (uint64_t i = 0; i < generalData->size; i++) {

        (generalData->vectors)[i] = (int64_t *) malloc((generalData->dimension) * sizeof(int64_t));
        if ((generalData->vectors)[i] == NULL) return -1;

        for (uint32_t j = 0; j < (generalData->dimension); j++) {
            (generalData->vectors)[i][j] = (int64_t) be64toh(buffer[i * (generalData->dimension) + j]);
        }
    }
    free(dimension);
    free(size);
    free(buffer);
    return 0;
}