#!/bin/bash

rm -f tests_files/test_performances/performances.txt

for nThreads in 1 2 3 4 5 6 7 8; do
  echo $nThreads >> "tests_files/test_performances/performances.txt"
  time -a -p -o "tests_files/test_performances/performances.txt" ./kmeans -k 5 -p 8 -q -t -n $nThreads -d euclidean\
          -f "tests_files/output_csv/ex7_50Kpoints_dim5.csv" "tests_files/input_binary/ex7_50Kpoints_dim5.bin"
done

python3 tests_files/test_performances/plotPerformances.py

