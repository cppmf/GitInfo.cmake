# ---------------------------------------------------------------------------- #
# CppMF projects are designed to apply modern CMake practice.
# As such, a decent CMake version is used to benefit from all new features.
#
# Check CMake Release Notes:
#   https://cmake.org/cmake/help/latest/release/3.21.html
# ---------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

# Make use of GetCPM.cmake
include(${CMAKE_CURRENT_LIST_DIR}/cmake/GetCPM.cmake)

# Add Version.cmake package
CPMAddPackage(NAME GitInfo.cmake SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)


# ---------------------------------------------------------------------------- #
# Git
# ---------------------------------------------------------------------------- #
GitInfo(${CMAKE_CURRENT_SOURCE_DIR}/..)


# ---------------------------------------------------------------------------- #
# Project configuration
# ---------------------------------------------------------------------------- #
project(
  TestApp
  VERSION 1.0.0
  LANGUAGES CXX
)


# ---------------------------------------------------------------------------- #
# Display git info
# ---------------------------------------------------------------------------- #
if(GIT_INFO_CMAKE_INFO)
  GitInfoReport()
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
