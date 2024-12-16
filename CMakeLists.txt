cmake_minimum_required(VERSION 3.10)
project(GBM)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include/ directory to the compiler's search paths
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the executable and its source files
add_executable(gbm
  src/main.cpp
  src/dataset.cpp
)
