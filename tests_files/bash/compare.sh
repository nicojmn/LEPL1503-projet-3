#!/bin/bash

ACTUAL="tests_files/output_csv/actual.csv"
EXPECTED="tests_files/output_csv/expected.csv"

python3 tests_files/python/compare_solutions.py $ACTUAL $EXPECTED

# We check if compare_solutions.py worked out properly
if [ $? != 0 ];
then
    exit 1
fi
exit 0