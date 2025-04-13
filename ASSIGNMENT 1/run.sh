#!/bin/bash

# Clear the outputs directory if it exists
outputs_directory="./outputs"
if [ -d "$outputs_directory" ]; then
    rm -rf "$outputs_directory"/*
fi

# Input file
input_file_name="inputs/E1/1000 transactions.txt"

echo "Compiling BOCC"
g++ -std=c++17 BOCC-CTA-CS21BTECH11022.cpp Transaction.cpp -o bocc.out

echo "Compiling FOCC-aborting current transaction"
g++ -std=c++17 FOCC-CTA-CS21BTECH11022.cpp Transaction.cpp -o focc_c.out

echo "Compiling FOCC-Aborting other transaction"
g++ -std=c++17 FOCC-OTA-CS21BTECH11022.cpp Transaction.cpp -o focc_o.out

# Comment lines 21-27 to run the experiments before running loops
echo "Executing BOCC"
./bocc.out "$input_file_name"
echo "Executing FOCC-CTA"
./focc_c.out "$input_file_name"
echo "Executing FOCC-OTA"
./focc_o.out "$input_file_name"

# Uncomment lines 29-35 to execute with checking memory leaks
# echo "Executing BOCC"
# valgrind ./bocc.out "$input_file_name"
# echo "Executing FOCC-CTA"
# valgrind ./focc_c.out "$input_file_name"
# echo "Executing FOCC-OTA"
# valgrind ./focc_o.out "$input_file_name"

# Uncomment lines 37-47 to run loops
# for input_file_name in ./inputs/*/*.txt; do
#     echo "Experiment: $input_file_name"
#     ./bocc.out "$input_file_name"
#     ./focc_c.out "$input_file_name"
#     ./focc_o.out "$input_file_name"
#     outputs_directory="./outputs"
#     if [ -d "$outputs_directory" ]; then
#         rm -rf "$outputs_directory"/*
#     fi
# done