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
 * Loads the data from the input inputFile and store it in the data_t structure
 * @param inputFile : the binary inputFile to read
 * @param generalData : the data read from the inputFile
 * @return 0 if load succeed, -1 if error occurs
 */
int32_t loadData(FILE *inputFile, data_t *generalData);

#endif
