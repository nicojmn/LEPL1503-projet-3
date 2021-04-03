//
// Created by pierre on 02.04.21.
//

#include "../headers/createOutputFile.h"

//TODO make tests for csvFileHeadline function
void csvFileHeadline(bool quiet, FILE *outputPath){
    char *dataNames = malloc(46*sizeof(char));
    dataNames = "initialization centroids,distortion,centroids"; /*45*/
    fprintf(outputPath, "%s", dataNames);

    if (!quiet) {
        char *suppDataNames = malloc(9*sizeof(char));
        suppDataNames = ",clusters";
        fprintf(outputPath, "%s", suppDataNames);
        free(suppDataNames);
    }

    free(dataNames);
}

//TODO make tests for writeOneKmeans function
void writeOneKmeans(k_means_t *kMeans, bool quiet, FILE *outputPath, point_t *startingCentroids, int32_t iterationNumber){
    /*int64_t **startingCentroids = malloc(sizeof(int64_t)*(kMeans->dimension)*(kMeans->k));
    for (int i = 0; i < kMeans->k; ++i) {
        char *vector = malloc();
        for (int j = 0; j < kMeans->dimension; ++j) {

        }
    }
     fprintf(outputPath, "\"[(1, 1), (2, 2)]\",", );

    //TODO malloc all elements to write, format and write them

    fprintf(outputPath,"\n");

    free(toWrite); */
}

int64_t writeOneKmeansBis(bool quiet) {
    FILE *fpt;
    fpt = fopen("output.csv", "a+");
    if (fpt == NULL) {
        return -1;
    }

    char onVerification[46];
    char *dataNames = (char *) malloc(sizeof(char) * 46);
    if (dataNames == NULL) {
        return -1;
    }
    dataNames = "initialization centroids,distortion,centroids";


    fgets(onVerification, sizeof(onVerification), fpt);

    if (!strcmp(onVerification, dataNames)) { /* ici on vérifie au cas où le fichier vient d'être créé la première ligne et si non on fait les headers*/
        fprintf(fpt, "%s", dataNames);
        if (!quiet) {
            char *suppDataNames = malloc(9*sizeof(char));
            suppDataNames = ",clusters";
            fprintf(fpt, "%s", suppDataNames);
            free(suppDataNames);
        }
    }
    free(dataNames);

    /**
     * initialization est faite, il faut faire l'ajout des différents Kmeans
     *
     */
}