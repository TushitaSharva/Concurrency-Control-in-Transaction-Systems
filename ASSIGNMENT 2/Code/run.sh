#!/bin/bash

# Clear the outputs directory if it exists
outputs_directory="./outputs"
if [ -d "$outputs_directory" ]; then
    rm -rf "$outputs_directory"/*
fi

# Input file
input_file_name="inp.txt"

echo "Compiling BTO"
g++ -std=c++17 BTO-CS21BTECH11022.cpp -o bto.out

echo "Compiling MVTO"
g++ -std=c++17 MVTO-CS21BTECH11022.cpp -o mvto.out

echo "Compiling MVTO-gc"
g++ -std=c++17 MVTO-gc-CS21BTECH11022.cpp -o mvto_g.out

echo "Compiling k-MVTO"
g++ -std=c++17 k-MVTO-CS21BTECH11022.cpp -o mvto_k.out

# Comment lines 21-27 to run the experiments before running loops
echo "Executing BTO"
valgrind ./bto.out "$input_file_name"

echo "Executing MVTO"
valgrind ./mvto.out "$input_file_name"

echo "Executing MVTO-gc"
valgrind ./mvto_g.out "$input_file_name"

echo "Executing k-MVTO"
valgrind ./mvto_k.out "$input_file_name"

# Uncomment lines 29-35 to execute with checking memory leaks
# echo "Executing BTO"
# valgrind ./bto.out "$input_file_name"

# echo "Executing MVTO"
# valgrind ./mvto.out "$input_file_name"

# echo "Executing MVTO-gc"
# valgrind ./mvto_g.out "$input_file_name"

# echo "Executing k-MVTO"
# valgrind ./mvto_k.out "$input_file_name"

# Uncomment lines 37-47 to run loops
# for input_file_name in ./inputs/*/*.txt; do
#     echo "Experiment: $input_file_name"
#     ./bto.out "$input_file_name"
#     ./mvto.out "$input_file_name"
#     ./mvto_g.out "$input_file_name"
#     ./mvto_k.out "$input_file_name"
#     echo "\n\n"

#     outputs_directory="./outputs"
#     if [ -d "$outputs_directory" ]; then
#         rm -rf "$outputs_directory"/*
#     fi
# done