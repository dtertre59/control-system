# Definir la versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

project(Control_system)

# Sets
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


# Add subdirectories
add_subdirectory("${PROJECT_SOURCE_DIR}")
add_subdirectory("tests")
