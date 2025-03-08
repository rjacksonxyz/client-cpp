cmake_minimum_required(VERSION 3.14)
project(polygonio VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Download CPM.cmake if not already available
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
  message(STATUS "Downloading CPM.cmake")
  file(DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.6/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    EXPECTED_HASH SHA256=11c3fa5f1ba14f15d31c2fb63dbc8628ee133d81c8d764caad9a8db9e0bacb07
  )
endif()
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

# Add the json dependency with CPMAddPackage
CPMAddPackage(
  NAME nlohmann_json
  GITHUB_REPOSITORY nlohmann/json
  VERSION 3.11.2
  OPTIONS
    "JSON_BuildTests OFF"
)

# Define source files for our library
# Updated to reflect the new directory structure
file(GLOB_RECURSE LIBRARY_SOURCES
    "src/*.cpp"
)

# Define header files for our library
# Updated to reflect the new directory structure
file(GLOB_RECURSE LIBRARY_HEADERS
    "src/*.h"
    "src/*.hpp"
)

# Create a static library target
add_library(${PROJECT_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS}
)

# Experimental
# Add this line to explicitly set the linker language
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# Set up include directories for our library
# Modified to make the src directory a public include path
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link our library with the json dependency
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        nlohmann_json::nlohmann_json
)

# Add an example executable
add_executable(example examples/example.cpp)
target_link_libraries(example 
    PRIVATE 
        ${PROJECT_NAME}
        nlohmann_json::nlohmann_json
)

# Option for building tests
option(BUILD_TESTS "Build the tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()