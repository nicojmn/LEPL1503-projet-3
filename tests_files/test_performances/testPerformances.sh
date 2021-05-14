#!/bin/bash

rm -f tests_files/test_performances/performances.txt

# run an instance of the problem 8 times with different number of threads to compare the execution time
for nThreads in 1 2 3 4 5 6 7 8; do
  echo "===================================="
  echo "Start the run with $nThreads thread(s)"
  echo $nThreads >> "tests_files/test_performances/performances.txt"
  time -a -p -o "tests_files/test_performances/performances.txt" ./kmeans -k 5 -p 8 -q -t -n $nThreads -d euclidean\
          -f "tests_files/output_csv/ex7_50Kpoints_dim5.csv" "tests_files/input_binary/ex7_50Kpoints_dim5.bin"
  echo "Done !"
done

python3 tests_files/test_performances/plotPerformances.py
echo "You can find the result in tests_files/test_performances/figPerformances.png"
