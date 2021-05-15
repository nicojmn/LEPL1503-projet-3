#!/bin/bash

##########################
# run our helgrind tests #
##########################

echo "==========================
||  Version without -q  ||
=========================="

for nThreads in 1 4 8; do
  echo " | | | | | Runnig helgrind test with $nThreads thread(s) | | | | |"
  valgrind --tool=helgrind ./kmeans -k 2 -p 3 -n $nThreads -t -d euclidean -f tests_files/output_csv/kmeans.csv \
    tests_files/input_binary/ex3.bin
  echo "Done with $nThreads thread(s)"
done

echo "=======================
||  Version with -q  ||
======================="
for qNThreads in 1 4 8; do
  echo "| | | | | Runnig helgrind test with $qNThreads thread(s) | | | | |"
  valgrind --tool=helgrind ./kmeans -k 2 -p 3 -n $qNThreads -t -q -d euclidean -f tests_files/output_csv/kmeans.csv \
    tests_files/input_binary/ex3.bin
  echo "| | | | | Done with $qNThreads thread(s) | | | | |"
done
