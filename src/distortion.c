
#include "../../lepl1503-2021-skeleton/headers/distortion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/** Function not tested yet */
int64_t distortion(cluster_t *clusters, int32_t dimension, char *squaredDistance){
    char manhattan[] = "manhattan";
    char euclidean[] = "euclidean";
    int64_t distortionSum = 0;

    for (int i = 0; i < kMeans.k; ++i) {        //Pas sûr du Kmeans.k
        for (int j = 0; j < clusters->size; ++j) {      //Pas sûr du cluster->size -> ptt mettre dimension
            if (strcmp(squaredDistance, manhattan) == 0){
                distortionSum += squared_manhattan_distance(clusters[i].points[j], clusters[i].centroid, dimension);
            }
            else if (strcmp(squaredDistance, euclidean) == 0){
                distortionSum += squared_euclidean_distance(clusters[i].points[j], clusters[i].centroid, dimension);
            }
        }
    }
    return distortionSum;
}


