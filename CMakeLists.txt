cmake_minimum_required(VERSION 3.20)
project(RubikSimulator CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compiler flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4)
endif()

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# Add library
add_library(RubikSimulator ${SOURCES} ${HEADERS})
# Add executable
add_executable(TheRubikSimulator main.cpp ${SOURCES} ${HEADERS})

# Include directories
include_directories(include)

# Set output directory for build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)


# Run target
add_custom_target(run
    COMMAND TheRubikSimulator
    DEPENDS TheRubikSimulator
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)


# Testing
enable_testing()
add_subdirectory(tests)
