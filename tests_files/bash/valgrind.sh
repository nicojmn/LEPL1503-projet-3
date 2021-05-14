#!/bin/bash

echo "=========================
||  Version without -q  ||
========================="

valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./kmeans  -k 4 -p 6 -n 4 -t \
							-d manhattan -f tests_files/output_csv/kmeans.csv  tests_files/input_binary/ex3.bin
echo "=======================
||  Version with -q  ||
======================="

valgrind  --leak-check=full --leak-resolution=med --track-origins=yes --vgdb=no ./kmeans  -k 4 -p 6 -n 4 -q -t \
							-d manhattan -f tests_files/output_csv/kmeans.csv  tests_files/input_binary/ex3.bin