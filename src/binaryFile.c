#include <stdio.h>
#include "../headers/binaryFile.h"
#include <unistd.h>
#include <stdio.h>
#include <limits.h>


int32_t loadData(FILE *file, data_t *data) {

    uint32_t *dimension = (uint32_t *) malloc(sizeof(uint32_t));
    if (dimension == NULL) return -1;
    fread(dimension, 4 * sizeof(char), 1, file);
    data->dimension = (uint32_t) be32toh(*dimension);
    fseek(file, 4, SEEK_SET);

    uint64_t *size = (uint64_t *) malloc(sizeof(uint64_t));
    if (size == NULL) return -1;
    fread(size, 8 * sizeof(char), 1, file);
    data->size = (uint64_t) be64toh(*size);

    fseek(file, 12, SEEK_SET);

    int64_t *buffer = (int64_t *) malloc((data->dimension) * (data->size) * sizeof(int64_t));
    if (buffer == NULL) return -1;

    fread(buffer, 8 * sizeof(char), (data->dimension) * (data->size), file);

    data->vectors = (int64_t **) malloc(data->size * sizeof(int64_t * ));
    for (int64_t i = 0; i < data->size; i++) {

        (data->vectors)[i] = (int64_t *) malloc((data->dimension) * sizeof(int64_t));
        if ((data->vectors)[i] == NULL) return -1;

        for (uint32_t j = 0; j < (data->dimension); j++) {
            (data->vectors)[i][j] = (int64_t) be64toh(buffer[i * (data->dimension) + j]);
        }
    }
    free(dimension);
    free(size);
    free(buffer);
    return 0;
}