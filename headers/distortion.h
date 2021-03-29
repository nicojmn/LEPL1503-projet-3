
#ifndef DISTORTION_H
#define DISTORTION_H
#include <stdint.h>

#include "cluster.h"
#inlcude "kMeans.h"
#include "distance.h"

/**
 *
 */

void distortion(cluster_t *clusters, char squaredDistance);

#endif //DISTORTION_H
