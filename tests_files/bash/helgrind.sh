#!/bin/bash

echo "=========================
||  Version without -q  ||
========================="

valgrind --tool=helgrind ./kmeans -k 2 -p 3 -n 2 -t -d euclidean -f tests_files/output_csv/kmeans.csv \
        tests_files/input_binary/ex3.bin

echo "=======================
||  Version with -q  ||
======================="

valgrind --tool=helgrind ./kmeans -k 2 -p 3 -n 2 -t -q -d euclidean -f tests_files/output_csv/kmeans.csv \
        tests_files/input_binary/ex3.bin