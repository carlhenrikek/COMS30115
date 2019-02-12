cmake_minimum_required(VERSION 3.2)
project(ComputerGraphics LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(OpenGL REQUIRED)
message(STATUS "OpenGL included at ${OPENGL_INCLUDE_DIR}")
add_definitions(${OPENGL_DEFINTIONS})

find_package(SDL2 REQUIRED)
message(STATUS "SDL 2 included at ${SDL2_INCLUDE_DIR}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(starfield)
