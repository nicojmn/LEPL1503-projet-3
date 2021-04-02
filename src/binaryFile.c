#include <stdio.h>
#include "../headers/binaryFile.h"

int64_t writeFromBinaryFile (char *filename, int32_t *dimension, int64_t **vectors, int64_t *size) {
    int file = open(filename, O_RDONLY, S_IRUSR);
    if (file == -1) {
        return -1;
    }

    struct stat buf;
    if (fstat(file, &buf)) {
        close(file);
        return -1;
    }

    int64_t *addr = (int64_t *) mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, file, 0);
    if (addr == MAP_FAILED) {
        close(file);
        return -1;
    }

    dimension = (int32_t *) malloc(sizeof(int32_t));
    if (dimension == NULL) {
        return -1;
    }
    *dimension = *addr;

    size = (int64_t *) malloc(sizeof(int64_t));
    if (size == NULL) {
        return -1;
    }
    *size = 11;

    vectors = (int64_t **) malloc(sizeof(int64_t *)*(*size));
    if (vectors == NULL) {
        return -1;
    }

    printf("%ld %d fin" ,*size, *dimension);
    int counter = 0;
    for (int32_t i = 0; i < *size; i++) {
        vectors[i] = (int64_t *) malloc(sizeof(int64_t)*(*dimension));
        if (vectors[i] == NULL) {
            return -1;
        }
        for (int32_t j = 0; j < *dimension; j++) {
            vectors[i][j] = addr[2 + i + j];
            counter++;
        }

    }
    printf("yolo");

    if (close(file) == -1) {
        munmap(addr, buf.st_size);
        return -1;
    }

    int ferm = munmap(addr, buf.st_size);
    if (ferm == -1) {
        return -1;
    }

    return 0;
}