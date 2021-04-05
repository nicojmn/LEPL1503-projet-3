#ifndef BINARYFILE_H
#define BINARYFILE_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <ftw.h>
#include <stdlib.h>
#include "../headers/kMeans.h"
int32_t loadData(FILE *file, data_t *data);

#endif //BINARYFILE_H
