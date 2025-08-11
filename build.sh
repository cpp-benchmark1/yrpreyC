#!/bin/bash

# Enhanced build script for YrpreyC vulnerabilities
# Handles both single-file and multi-file C++ projects

echo "🔨 Building YrpreyC vulnerabilities..."

# Function to compile a directory
compile_directory() {
    local dir="$1"
    local dir_name=$(basename "$dir")
    
    echo "📁 Processing directory: $dir_name"
    
    # Check if directory has a Makefile
    if [ -f "$dir/Makefile" ]; then
        echo "  📋 Using Makefile for $dir_name"
        cd "$dir"
        make clean 2>/dev/null || true
        make
        cd - > /dev/null
        return
    fi
    
    # Check if directory has multiple .cpp files
    local cpp_files=()
    while IFS= read -r -d '' file; do
        cpp_files+=("$file")
    done < <(find "$dir" -maxdepth 1 -name "*.cpp" -print0 | sort -z)
    
    local header_files=()
    while IFS= read -r -d '' file; do
        header_files+=("$file")
    done < <(find "$dir" -maxdepth 1 -name "*.h" -print0 | sort -z)
    
    if [ ${#cpp_files[@]} -eq 0 ]; then
        echo "  ⚠️  No .cpp files found in $dir_name"
        return
    fi
    
    if [ ${#cpp_files[@]} -eq 1 ]; then
        # Single file compilation
        local cpp_file="${cpp_files[0]}"
        local base_name=$(basename "$cpp_file" .cpp)
        local output_name="$dir/$base_name"
        
        echo "  🔧 Compiling single file: $base_name.cpp"
        g++ -std=c++11 -Wall -Wextra -o "$output_name" "$cpp_file"
        
        if [ $? -eq 0 ]; then
            echo "  ✅ Successfully compiled: $output_name"
        else
            echo "  ❌ Failed to compile: $base_name.cpp"
        fi
    else
        # Multi-file compilation
        echo "  🔧 Compiling multi-file project: $dir_name"
        
        # Find main file (usually contains main() function)
        local main_file=""
        for cpp_file in "${cpp_files[@]}"; do
            if grep -q "int main(" "$cpp_file" 2>/dev/null; then
                main_file="$cpp_file"
                break
            fi
        done
        
        if [ -z "$main_file" ]; then
            # If no main found, use first .cpp file
            main_file="${cpp_files[0]}"
        fi
        
        local base_name=$(basename "$main_file" .cpp)
        local output_name="$dir/$base_name"
        
        # Compile all .cpp files together
        echo "  📦 Compiling ${#cpp_files[@]} files together"
        g++ -std=c++11 -Wall -Wextra -o "$output_name" "${cpp_files[@]}" 2>/dev/null || {
            echo "  ⚠️  Multi-file compilation failed, trying single file compilation..."
            for cpp_file in "${cpp_files[@]}"; do
                local single_base=$(basename "$cpp_file" .cpp)
                local single_output="$dir/$single_base"
                echo "  🔧 Compiling single file: $single_base.cpp"
                g++ -std=c++11 -Wall -Wextra -o "$single_output" "$cpp_file"
            done
        }
        
        if [ $? -eq 0 ]; then
            echo "  ✅ Successfully compiled: $output_name"
        else
            echo "  ❌ Failed to compile multi-file project: $dir_name"
        fi
    fi
}

# Find all vulnerability directories
find . -maxdepth 1 -type d -name "* - *" | sort | while IFS= read -r dir; do
    if [ -d "$dir" ]; then
        compile_directory "$dir"
        echo ""
    fi
done

echo "🎉 Build process completed!" 