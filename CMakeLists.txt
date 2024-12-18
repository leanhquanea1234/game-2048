# Minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project Name
project(GAME 2048 v0.1)

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

# Add SFML include and library directories
set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/SFML")
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)

# Find SFML package and link libraries
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(2048 sfml-system sfml-window sfml-graphics)

# Cross-platform libraries
# if(WIN32)
#     # Add PDCurses for Windows
#     find_library(PDCURSES_LIBRARY pdcurses REQUIRED)
#     target_link_libraries(2048 ${PDCURSES_LIBRARY})
# elseif(UNIX)
#     # Add ncurses for Linux/macOS
#     find_package(Curses REQUIRED)
#     target_link_libraries(2048 ${CURSES_LIBRARIES})
# endif()
