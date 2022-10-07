# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.12)

project("Framework3D")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(FRAMEWORK_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(FRAMEWORK_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

set(SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders")

# Include sub-projects.
add_subdirectory(${FRAMEWORK_SOURCE_DIR})
