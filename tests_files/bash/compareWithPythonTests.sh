#!/bin/bash

runOneComparison() {

  echo "============================================================================================================
|| Comparison using: k = $1, p = $2, n = $3, distance function: $4 and the file $5 ||
============================================================================================================"

  # If it is a special case when the number of points < picking limit
  if [ $# = 6 ]; then
    echo '/!Special case with a picking limit exceeding the number of points!\'
  fi

  sh tests_files/bash/run.sh python $1 $2 $4 $3 $5
  sh tests_files/bash/run.sh c $1 $2 $4 $3 $5

  sh tests_files/bash/compare.sh

  # verify of no error occurred
  if [ $? != 0 ]; then
    # We delete the previous file
    rm "tests_files/comparisonResult.txt"
    # We write the outcome in a file so that our c script can be informed
    echo "FAIL" >>"tests_files/comparisonResult.txt"
    exit 1
  fi
}

# Arguments of runOneComparison: [k] [p] [n] [d] [inputFile]

# Comparison using the simple file ex1.bin
runOneComparison 2 4 1 euclidean ex1.bin
runOneComparison 2 4 2 manhattan ex1.bin
runOneComparison 2 5 3 euclidean ex1.bin

# Comparison with a picking limit exceeding the number of points
runOneComparison 3 30 2 euclidean ex1.bin "pickingLimitExceedingNbrPoints"

# Comparison using the file ex3.bin
runOneComparison 2 4 1 euclidean ex3.bin
runOneComparison 2 4 2 manhattan ex3.bin
runOneComparison 2 5 3 euclidean ex3.bin

# Comparison using the file ex6_dim5.bin
runOneComparison 2 4 4 euclidean ex6_dim5.bin

# Comparison using the file ex7_50Kpoints_dim5.bin

runOneComparison 3 4 7 euclidean ex7_50Kpoints_dim5.bin

# We delete the previous file
rm "tests_files/comparisonResult.txt"
# We write the outcome in a file so that our c script can be informed
echo "SUCCESS" >>"tests_files/comparisonResult.txt"
exit 0
