# ---------------------------------------------------------------------------- #
# CppMF projects are designed to apply modern CMake practice.
# As such, a decent CMake version is used to benefit from all new features.
#
# Check CMake Release Notes:
#   https://cmake.org/cmake/help/latest/release/3.21.html
# ---------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)


# Add the directory containing the main CMakeLists file
# and declare the output directory
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/GitInfoCmake)


# ---------------------------------------------------------------------------- #
# Git
# ---------------------------------------------------------------------------- #
GitInfo(${CMAKE_CURRENT_SOURCE_DIR}/..)


# ---------------------------------------------------------------------------- #
# Project configuration
# ---------------------------------------------------------------------------- #
project(
  test_app
  VERSION 1.0.0
  LANGUAGES CXX
)


# ---------------------------------------------------------------------------- #
# Display git info
# ---------------------------------------------------------------------------- #
if(GIT_INFO_CMAKE_INFO)
  GitInfoInfo()
endif()


# ---------------------------------------------------------------------------- #
# Pass definition to compiler
# ---------------------------------------------------------------------------- #
if(GIT_REVISION)
    add_definitions(-DGIT_REVISION="${GIT_REVISION}")
endif()
if(GIT_REVISION_NAME)
    add_definitions(-DGIT_REVISION_NAME="${GIT_REVISION_NAME}")
endif()


# ---------------------------------------------------------------------------- #
# Add target
# ---------------------------------------------------------------------------- #
add_executable(${PROJECT_NAME} main.cpp)


# ---------------------------------------------------------------------------- #
# Add test
# ---------------------------------------------------------------------------- #
enable_testing()
add_test(NAME test COMMAND ${PROJECT_NAME})
