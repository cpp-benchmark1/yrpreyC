#!/bin/bash

# Find all .cpp files in subdirectories and compile them
find . -type f -name "*.cpp" | while read -r cpp_file; do
    dir_name=$(dirname "$cpp_file")
    base_name=$(basename "$cpp_file" .cpp)
    output_name="${dir_name}/${base_name}"
    
    echo "Compiling $cpp_file to $output_name"
    g++ -o "$output_name" "$cpp_file"
done 