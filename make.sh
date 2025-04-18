#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <main file>"
    exit 1
fi

# Set directories
MAIN_FILE=$1
INCLUDE_DIR="./include"
LIB_DIR="./lib"
OUTPUT_DIR="build"
OUTPUT_FILE="$OUTPUT_DIR/run"

# Create the output directory if it doesn't exist
mkdir -p $OUTPUT_DIR

# Initialize arrays
while IFS= read -r file; do
    SRC_FILES+=("$file")
done < <(find "$INCLUDE_DIR" -type f \( -name "*.cpp" -o -name "*.c" \))

echo ${SRC_FILES[@]}
# Compile the program
# g++ -std=c++17 -g -o $OUTPUT_FILE $MAIN_FILE ${SRC_FILES[@]} -I$INCLUDE_DIR -L$LIB_DIR -lglfw3 -ldl -framework Cocoa -framework OpenGL -framework IOKit

# Compile the program
# g++ -std=c++17 -g -o $OUTPUT_FILE $MAIN_FILE ${SRC_FILES[@]} -I$INCLUDE_DIR -L$LIB_DIR -lassimp -lassimp.5 -lassimp.5.4.3 -lglfw3 -ldl -framework Cocoa -framework OpenGL -framework IOKit
g++ -std=c++17 -g -o $OUTPUT_FILE $MAIN_FILE ${SRC_FILES[@]} -I$INCLUDE_DIR -L$LIB_DIR -lassimp.5  -lglfw3 -ldl -framework Cocoa -framework OpenGL -framework IOKit

# Check for success
if [[ $? -eq 0 ]]; then
    echo "✅ Build successful: $OUTPUT_FILE"

    # Add rpath to the executable
    install_name_tool -add_rpath @loader_path/../lib $OUTPUT_FILE
    echo "✅ rpath added to executable"

    # Set DYLD_LIBRARY_PATH for runtime
    export DYLD_LIBRARY_PATH=$LIB_DIR:$DYLD_LIBRARY_PATH
    echo "✅ DYLD_LIBRARY_PATH set"

    # Run the executable
    ./$OUTPUT_FILE
else
    echo "❌ Build failed."
fi
