# SPDX-License-Identifier: GPL-3.0-or-later
# Copyright (C) 2025~2025 David SPORN
# ---
# This is part of **I/O pins**.
# A C++ abstraction layer for I/O pins of micro-controllers.
# ---

# Define how to build the test suite
set(BINARY ${CMAKE_PROJECT_NAME}--test)

# FIXME registers your cpp files from ../src
# e.g. : set(SOURCES TestRunner.cpp ../src/whatever.cpp)
set(SOURCES TestRunner.cpp)

add_executable(${BINARY} ${SOURCES})
target_include_directories(${BINARY} PUBLIC ../include)

# Uses criterion, see https://github.com/Snaipe/Criterion
find_library(LIBCRITERION criterion REQUIRED)
target_link_libraries(${BINARY} PRIVATE criterion)

# ---
# Create the custom task `verify` that MUST be invoked to run the test suite.
# i.e. `cmake --build . -- verify`
add_custom_target(
    verify COMMAND env CLICOLOR_FORCE=1 ${CMAKE_CTEST_COMMAND} --verbose
    DEPENDS ${BINARY}
)

# ---
# Specify how to launch the test suite, and how to check that it pass
enable_testing()
add_test(NAME DoTest COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${BINARY} --color=always)
