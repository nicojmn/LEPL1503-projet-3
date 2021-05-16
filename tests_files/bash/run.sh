#!/bin/bash

################################################################################
# this bash script can run either a c or python execution of Lloyd's algorithm #
################################################################################

# Method used (python or c)
MODE=$1
# Number of centroid(s)
K=$2
# Number of points considered for being centroid
P=$3
# Distance function
DISTANCE_FUNCTION=$4
# Number of thread
N=$5
# Input file
INPUT_FILE="tests_files/input_binary/$6"

if [ "$MODE" = "python" ]; then
  OUTPUT_FILE="tests_files/output_csv/expected.csv"
  python3 tests_files/python/k-means.py -k $K -p $P -t True -d $DISTANCE_FUNCTION -f $OUTPUT_FILE $INPUT_FILE
else
  OUTPUT_FILE="tests_files/output_csv/actual.csv"
  ./kmeans -k $K -p $P -n $N -d $DISTANCE_FUNCTION -t -f $OUTPUT_FILE $INPUT_FILE
fi

