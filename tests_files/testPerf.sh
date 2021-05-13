#!/bin/bash


rm -f tests_files/comparisonResult.txt

for i in 1 2 3 4 5 6 7 8
do 
    echo "$i" >> "tests_files/comparisonResult.txt"
    time -a -p -o "tests_files/comparisonResult.txt" ./kmeans -k 4 -p 7 -n $i -d euclidean -t -f "output_csv/ex6_dim5.csv" "input_binary/ex6_dim5.bin"
done