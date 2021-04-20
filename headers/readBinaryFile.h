#ifndef BINARYFILE_H
#define BINARYFILE_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <ftw.h>
#include <stdlib.h>

#include "kMeans.h"

/**
 *
 * @param file : the binary file to read
 * @param data : the data read from the file
 * @return 0 if load succeed, -1 if error occurs
 */
int32_t loadData(FILE *file, data_t *data);

#endif
