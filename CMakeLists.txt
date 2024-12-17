cmake_minimum_required(VERSION 3.10)
project(GBM)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add the include/ directory to the compiler's search paths
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(gbm
  src/main.cpp
  src/dataset.cpp
)

# GoogleTest
add_subdirectory(googletest)

add_executable(tests
  tests/dataset_test.cpp
  tests/main_test.cpp
  src/dataset.cpp
)

# Link the test executable with GoogleTest
target_link_libraries(tests gtest gtest_main)

# Add tests
add_test(NAME GBMTests COMMAND tests)
