cmake_minimum_required(VERSION 3.14)
project(polygonio VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
  message(STATUS "Downloading CPM.cmake")
  file(DOWNLOAD
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.6/CPM.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
    EXPECTED_HASH SHA256=11c3fa5f1ba14f15d31c2fb63dbc8628ee133d81c8d764caad9a8db9e0bacb07
  )
endif()
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
cmake_policy(SET CMP0167 NEW)
find_package(Boost REQUIRED COMPONENTS system thread json)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost library not found")
endif()

# Add before find_package(OpenSSL REQUIRED)
# set(CMAKE_FIND_DEBUG_MODE ON)
find_package(OpenSSL REQUIRED)

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

# Link library with dependencies
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Boost::system
        Boost::thread
        Boost::json
        ${OPENSSL_SSL_LIBRARY}
        ${OPENSSL_CRYPTO_LIBRARY}
)

# Add example executable
add_executable(example examples/example.cpp)
target_link_libraries(example 
    PRIVATE 
        ${PROJECT_NAME}
        Boost::system
        Boost::thread
        Boost::json
        ${OPENSSL_SSL_LIBRARY}
        ${OPENSSL_CRYPTO_LIBRARY}
)

# Option for building tests
option(BUILD_TESTS "Build the tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
