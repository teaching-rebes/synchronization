cmake_minimum_required(VERSION 3.13)  # CMake version check

project(synchronization)              # Create project

set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Include the current directory as search path
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES_SYNCHRONIZATION synchronization.cpp BankAccount.cpp)
set(SOURCE_FILES_PRODUCER_CONSUMER prodcon.cpp)

SET(GCC_COVERAGE_COMPILE_FLAGS "-static ")
SET(GCC_COVERAGE_LINK_FLAGS    "")

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(synchronization ${SOURCE_FILES_SYNCHRONIZATION})
add_executable(prodcon ${SOURCE_FILES_PRODUCER_CONSUMER})

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
