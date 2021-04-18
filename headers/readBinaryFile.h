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
 * #TODO Signature
 * @param file
 * @param data
 * @return
 */
int32_t loadData(FILE *file, data_t *data);

#endif
