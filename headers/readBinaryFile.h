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
 * Loads the data from the binary input file and store it in the data_t structure
 * @param inputFile : the binary input file to read
 * @param generalData : the instance's characteristics and all the points from the input file
 * @return 0 if load succeed, -1 if error occurs
 */
int32_t loadData(FILE *inputFile, data_t *generalData);

#endif
