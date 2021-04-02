#ifndef BINARYFILE_H
#define BINARYFILE_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <ftw.h>
#include <stdlib.h>
#include "../headers/kMeans.h"
int64_t writeFromBinaryFile (char *filename, int32_t *dimension, int64_t **vectors, int64_t *size);

#endif //BINARYFILE_H
