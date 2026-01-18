cmake_minimum_required(VERSION 3.10)
project(HomemadeScikit VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Library sources
set(SCIKIT_SOURCES
    src/dataset.cpp
    src/utils.cpp
    src/model.cpp
)

# Create library
add_library(homemadescikit ${SCIKIT_SOURCES})

# Examples
add_executable(single_weight_example examples/single_weight_example.cpp)
target_link_libraries(single_weight_example homemadescikit)

add_executable(multiple_regression examples/multiple_regression.cpp)
target_link_libraries(multiple_regression homemadescikit)

# Tests
enable_testing()
add_executable(test_dataset tests/test_dataset.cpp)
target_link_libraries(test_dataset homemadescikit)
add_test(NAME DatasetTest COMMAND test_dataset)
