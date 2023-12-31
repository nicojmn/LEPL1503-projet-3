#ifndef DISTANCE_H
#define DISTANCE_H

#include <stdint.h>

#include "kMeansStruct.h"


/**
 * @param x : int64_t number
 * @return : the absolute value of x
 */
uint64_t absVal(int64_t x);

/**
 * This typedef below defines the distance_func_t type, a function pointer type that groups all
 * functions with the following signature :
 *
 *      int64_t function_name(const point_t *, const point_t *, int32_t)
 *
 * So basically, once you've implemented squared_manhattan_distance and squared_euclidean_distance,
 * you can do the following if you want:
 *
 *      squared_distance_func_t generic_func;
 *      if (some_condition) {
 *          generic_func = squared_manhattan_distance;
 *      } else {
 *          generic_func = squared_euclidean_distance;
 *      }
 *      uint64_t dist = generic_func(a, b, dimension); // computes either the manhattan distance or the euclidean distance depending on the some_condition
 *
 */
typedef uint64_t (*squared_distance_func_t)(const point_t *, const point_t *, uint32_t);

/**
 * @param p1 : first point
 * @param p2 : second point
 * @param dimension : the dimension of the points
 * @return the squared manhattan distance between 2 points
 */
uint64_t squared_manhattan_distance(const point_t *p1, const point_t *p2, uint32_t dimension);

/**
 * @param p1 : first point
 * @param p2 : second point
 * @param dimension : the dimension of the points
 * @return the squared euclidean distance between 2 points
 */
uint64_t squared_euclidean_distance(const point_t *p1, const point_t *p2, uint32_t dimension);

#endif
