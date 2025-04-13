#!/bin/bash

# Loop through all Python files in the current directory
for python_file in *.py; do
    # Extract the base name (filename without extension)
    base_name=$(basename "$python_file" .py)

    # Run the Python file
    python3 "$python_file"

    if [ $? -eq 0 ]; then
        echo "Executed $python_file and saved the plot as $base_name.png"
    else
        echo "Failed to run $python_file or no plot generated."
    fi
done