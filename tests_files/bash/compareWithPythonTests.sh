#!/bin/bash

echo "run python on ex1.bin with k = 2 and p = 3"
sh tests_files/bash/run.sh python 2 3 euclidean 1 ex1.bin

echo "run c on ex1.bin with k = 2, p = 3 and n = 1"
sh tests_files/bash/run.sh c 2 3 euclidean 1 ex1.bin

sh tests_files/bash/compare.sh
