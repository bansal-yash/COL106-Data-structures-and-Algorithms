#!/bin/bash

g++ -o my_program main.cpp

start=$(date +%s%N)  # Get start time in nanoseconds
./my_program < test1.txt > output.txt
end=$(date +%s%N)    # Get end time in nanoseconds

# Calculate total time in milliseconds (end - start) / 1,000,000
total_time=$(( (end - start) / 1000000 ))

if cmp -s output.txt result1.txt; then
    echo "All tests passed: Output matches result1.txt"
    tests_passed=true
else
    echo "Some tests failed: Output does not match result1.txt"
    tests_passed=false
fi

total_test_cases=$(wc -l < test1.txt)
if [ "$tests_passed" = true ]; then
    test_cases_passed=$total_test_cases
else
    diff_output=$(diff -u output.txt result1.txt | grep -E "^\+[0-9]" | wc -l)
    test_cases_passed=$((total_test_cases - diff_output))
fi

echo "Total test cases: $total_test_cases"
echo "Test cases passed: $test_cases_passed"
echo "Total time taken: $total_time milliseconds"

rm my_program output.txt
