#ifndef MANAGEARGS_H
#define MANAGEARGS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <errno.h>

#include "kMeans.h"


/**
 * Structure gathering all the arguments given in command line
 */
typedef struct {
    FILE *input_stream;
    FILE *output_stream;
    uint32_t n_threads;
    uint32_t k;
    uint32_t n_first_initialization_points;
    bool quiet;
    bool test_mode;
    squared_distance_func_t squared_distance_func;
} args_t;

/**
 * @param prog_name : the name of the program
 *  it display into the terminal all the possible options available
 */
void usage(char *prog_name);

/**
 * @param args : the structure which will gather all the arguments
 * @param argc : number of argument passed to the program
 * @param argv : the arguments passed to the program
 * @return : The function writes each argument from arv to the structure args
 *           it returns 1 if no problem occurred, -1 otherwise
 */
int parse_args(args_t *args, int argc, char *argv[]);

/**
 * @param programArguments : structure which gather the program arguments
 * @return : 1 if the argument are valid and -1 otherwise
 */
int32_t verifyArguments(args_t programArguments);

/**
 * @param programArguments : structure which gather the program arguments
 *      It displays a recap of the current program argument if the test_mode is not enabled
 */
void displayOptions(args_t programArguments);

#endif //MANAGEARGS_H
