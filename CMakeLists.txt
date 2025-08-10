# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright (C) 2025~2025 David SPORN
# ---
# This is part of **I/O pins**.
# An abstraction layer for I/O pins of micro-controllers.
# ---
# This is a source library project. As such, no deliverable binary is generated.
#
# HOWEVER there is a test suite that can be compiled and invoked
# ---
# How to build and verify
#
# 1. Create a build directory : `mkdir built-tests`
# 2. Change to this build directory : `cd build-tests`
# 3. Initialize the build system : `cmake ..`
# 4. Invoke the build system to perform the test suite :
#    * either `cmake --build . -- verify` to build incrementally.
#    * or `cmake --build . --clean-first -- verify` to trigger a full rebuild.
# ---
cmake_minimum_required(VERSION 3.28)
project(io_pins)
set(CMAKE_CXX_STANDARD 23)
add_compile_options(-Wall -Wextra -Wpedantic)

# Generate the db for clang toolings by default
# need to call supplemental target
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("export compile command is ${CMAKE_EXPORT_COMPILE_COMMANDS}")

# The test suite is implemented in a dedicated source folder.
add_subdirectory(src-tests)

# Add clang-format tasks
file(GLOB_RECURSE FORMATTABLE_SOURCES
       ${PROJECT_SOURCE_DIR}/include/*.hpp
       ${PROJECT_SOURCE_DIR}/src/*.cpp
       ${PROJECT_SOURCE_DIR}/src-tests/*.cpp
)

# Custom targets for pretty printing the sources (check and perform)
add_custom_target(check-prettier
    COMMAND clang-format
    --verbose
    --dry-run
    --style=file
    ${FORMATTABLE_SOURCES}
)
add_custom_target(prettier
    COMMAND clang-format
    --verbose
    -i
    --style=file
    ${FORMATTABLE_SOURCES}
)

# Custom target to manage compile_commands.json
# requires compdb : https://github.com/Sarcasm/compdb
add_custom_target(refresh-compile-db
    COMMAND compdb
    -p ${CMAKE_BINARY_DIR}
    list
    > ${PROJECT_SOURCE_DIR}/compile_commands.json
)

# Linter
add_custom_target(lint
    COMMAND clang-tidy-19
    ${FORMATTABLE_SOURCES}
    DEPENDS prettier refresh-compile-db
)

# Generate documentation
add_custom_target(doc-generate
    COMMAND doxygen
    ../Doxyfile-cmake
    DEPENDS prettier
)
