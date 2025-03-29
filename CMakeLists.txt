# Definir la versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

# Forzar version. forzar el uso de C++11 o superior:
# set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(Control_system)

# Sets
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


# Add subdirectories
add_subdirectory("${PROJECT_SOURCE_DIR}")
# add_subdirectory("tests")
