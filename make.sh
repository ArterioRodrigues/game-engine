#!/bin/bash

# Set directories
SRC_DIR="src"
INCLUDE_DIR="./include"
LIB_DIR="./lib"
OUTPUT_DIR="build"
OUTPUT_FILE="$OUTPUT_DIR/run"

# Create the output directory if it doesn't exist
mkdir -p $OUTPUT_DIR

# Initialize arrays
SRC_FILES=()
HEADER_FILES=()

# Populate arrays with files from the source directory
for file in $SRC_DIR/*; do
    if [[ $file == *.cpp || $file == *.c ]]; then
        SRC_FILES+=("$file")
    elif [[ $file == *.h ]]; then
        HEADER_FILES+=("$file")
    fi
done

# Print the files (for debugging purposes)
echo "Source files: ${SRC_FILES[@]}"
echo "Header files: ${HEADER_FILES[@]}"

# Compile the program
g++ -g -o $OUTPUT_FILE ${SRC_FILES[@]} -I$INCLUDE_DIR -L$LIB_DIR -lglfw3 -ldl -framework Cocoa -framework OpenGL -framework IOKit

# Check for success
if [[ $? -eq 0 ]]; then
    echo "Build successful: $OUTPUT_FILE"
    ./$OUTPUT_FILE
else
    echo "Build failed."
fi