#!/bin/bash

runOneComparison() {

    echo "\nComparison with k = $1, p = $2, n = $3 and the file $4:"

    sh tests_files/bash/run.sh python $1 $2 euclidean $3 $4
    sh tests_files/bash/run.sh c $1 $2 euclidean $3 $4

    sh tests_files/bash/compare.sh

    # verify of no error occurred
    if [ $? != 0 ]; then
      exit 1
    fi
}

# Comparison with the simple file ex1.bin
runOneComparison 2 4 1 ex1.bin
runOneComparison 2 4 2 ex1.bin
runOneComparison 2 5 3 ex1.bin

# Comparison with the file ex3.bin
runOneComparison 2 4 1 ex3.bin
runOneComparison 2 4 2 ex3.bin
runOneComparison 2 5 3 ex3.bin

# Comparison with the file ex6_dim.bin
runOneComparison 2 4 4 ex6_dim5.bin

exit 0