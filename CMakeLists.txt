# Definir la versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.10)

PROJECT (Control_system)

SET(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
SET(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}")