# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project Name
project(2048)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Source files
set(SOURCES
    src/main.cpp
    src/game_logic.cpp
    src/terminal_rendering.cpp
    src/user_input.cpp
)

# Include directories
include_directories(include)

# Add executable
add_executable(2048 ${SOURCES})

# Find SFML package
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib/SFML") # Optional: point to local SFML if needed
find_package(SFML COMPONENTS system window graphics REQUIRED)

# Link SFML libraries
target_link_libraries(2048 sfml-system sfml-window sfml-graphics)

