cmake_minimum_required(VERSION 3.10)
project(GBM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# If building on MSVC, ensure we use the shared (DLL) runtime.
if(MSVC)
    # This requires CMake 3.15+
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Force GoogleTest to use the shared runtime.
set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) runtime" FORCE)
add_subdirectory(googletest)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main executable
add_executable(gbm
  src/main.cpp
  src/dataset.cpp
)

# Tests
add_executable(tests
  tests/dataset_test.cpp
  tests/main_test.cpp
  src/dataset.cpp
)

target_link_libraries(tests gtest gtest_main)
add_test(NAME GBMTests COMMAND tests)

# Hardcoded Python paths (adjust these if needed)
set(PYTHON_EXECUTABLE "")
set(PYTHON_INCLUDE_DIR "")
set(PYTHON_LIBRARY "")

# Find Python3 (Interpreter & Development)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Add pybind11 subdirectory
add_subdirectory(pybind11)

# Create pybind11 module
pybind11_add_module(gbm_pybind
  src/py_wrapper.cpp
  src/dataset.cpp
)
