#!/bin/bash

# Check if the executable 'main' already exists and remove it
if [ -f main ]; then
    echo "Removing existing executable 'main'."
    rm main
fi

# Compile the C++ program
g++ -fsanitize=address -fsanitize=undefined -std=c++17 \
    -o main -Iinclude -Itest -Isrc \
    main.cpp \
    test/unit_test/hash/unit_test.cpp test/unit_test/heap/unit_test.cpp \
    -DTEST_HASH

