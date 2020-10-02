#
# Copyright (c) 2020 C++ Modern Framework
#

#
# GitInfo.cmake will extract git information from the project if :
#
#   - GIT_INFO_SOURCE_DIR is defined to the root of the project
#   - GIT_INFO_SOURCE_DIR have .git directory
#   - git is installed and found by cake
#
#
# Following variables will be set if preceding request are met:
#
#   GIT_DIR: path to the project .git directory
#   GIT_IS_DIRTY: whether or not the working tree is dirty
#   GIT_HEAD_BRANCH : name of the brack associated te HEAD
#   GIT_REVISION_HASH: current HEAD sha hash
#   GIT_REVISION: shorten version of GIT_REVISION_HASH
#   GIT_REVISION_NAME: name associated to GIT_REVISION_HASH
#   GIT_AUTHOR_NAME : author name
#   GIT_AUTHOR_EMAIL : author email
#   GIT_AUTHOR_DATE : author date
#   GIT_AUTHOR_DATE_ISO : author date, strict ISO 8601 format
#   GIT_COMMITTER_NAME : committer name
#   GIT_COMMITTER_EMAIL : committer email
#   GIT_COMMITTER_DATE : committer date
#   GIT_COMMITTER_DATE_ISO : committer date, strict ISO 8601 format
#   GIT_REMOTE_ORIGIN_URL : origin remote url
#   GIT_LATEST_TAG_LONG : most recent tag of the current branch
#   GIT_LATEST_TAG : most recent tagname of the current branch
#

message(STATUS "GIT_INFO_SOURCE_DIR : ${GIT_INFO_SOURCE_DIR}")


# GIT_INFO_SOURCE_DIR must be defined
if(NOT DEFINED GIT_INFO_SOURCE_DIR)
  message(FATAL_ERROR "GIT_INFO_SOURCE_DIR must be defined to point to the root project")
endif()

# GIT_INFO_SOURCE_DIR must exist
if(NOT EXISTS ${GIT_INFO_SOURCE_DIR})
  message(FATAL_ERROR "GIT_INFO_SOURCE_DIR is not a valid path")
endif()

# Define the possible location of the .git directory
set(GIT_DIR "${GIT_INFO_SOURCE_DIR}/.git")

# Check if .git folder exist
if(EXISTS ${GIT_DIR})

  # 
  set(GIT_DIR "${GIT_DIR}" CACHE PATH "Project .git directory")

  # Check if git is installed
  if(NOT GIT_FOUND)
    find_package(Git QUIET)
  endif()
  if(NOT GIT_FOUND)
    message(AUTHOR_WARNING "Git not found, cannot get git informations")
    return()
  endif()

  # whether or not the working tree is dirty
  execute_process(COMMAND ${GIT_EXECUTABLE} status --porcelain
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    RESULT_VARIABLE exit_code
    OUTPUT_VARIABLE GIT_IS_DIRTY OUTPUT_STRIP_TRAILING_WHITESPACE)
  # the working tree is dirty when the error code is different from 0
  # or if the output is not empty
  if(NOT exit_code EQUAL 0 OR NOT ${GIT_IS_DIRTY} STREQUAL "")
    set(GIT_IS_DIRTY ON CACHE BOOL "Indicate if current branch is dirty")
  else()
    set(GIT_IS_DIRTY OFF CACHE BOOL "Indicate if current branch is dirty")
  endif()

  # name of the brack associated te HEAD
  execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HEAD_BRANCH OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_HEAD_BRANCH "${GIT_HEAD_BRANCH}" CACHE INTERNAL "name of the brack associated te HEAD")

  # git revision full hash
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%H" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REVISION_HASH OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_INFO_SOURCE_DIR "${GIT_INFO_SOURCE_DIR}" CACHE INTERNAL "git revision full hash")
  
  # shorten version of git revision
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%h" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REVISION OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_REVISION "${GIT_REVISION}" CACHE INTERNAL "shorten version of git revision")

  # shorten version of git revision name
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%s" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REVISION_NAME OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_REVISION_NAME "${GIT_REVISION_NAME}" CACHE INTERNAL "shorten version of git revision name")

  # author name
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%an" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_AUTHOR_NAME OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_AUTHOR_NAME "${GIT_AUTHOR_NAME}" CACHE INTERNAL "git author name")

  # author email
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%ae" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_AUTHOR_EMAIL OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_AUTHOR_EMAIL "${GIT_AUTHOR_EMAIL}" CACHE INTERNAL "git author email")

  # author date
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%ad" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_AUTHOR_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_AUTHOR_DATE "${GIT_AUTHOR_DATE}" CACHE INTERNAL "git author date")

  # author date, strict ISO 8601 format
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%aI" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_AUTHOR_DATE_ISO OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_AUTHOR_DATE_ISO "${GIT_AUTHOR_DATE_ISO}" CACHE INTERNAL "git author date, strict ISO 8601 format")

  # committer name
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%cn" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMITTER_NAME OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_COMMITTER_NAME "${GIT_COMMITTER_NAME}" CACHE INTERNAL "git committer name")

  # committer email
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%ce" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMITTER_EMAIL OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_COMMITTER_EMAIL "${GIT_COMMITTER_EMAIL}" CACHE INTERNAL "git committer email")

  # committer date
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%cd" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMITTER_DATE OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_COMMITTER_DATE "${GIT_COMMITTER_DATE}" CACHE INTERNAL "git committer date")

  # committer date, strict ISO 8601 format
  execute_process(COMMAND ${GIT_EXECUTABLE} show -s "--format=%cI" HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMITTER_DATE_ISO OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_COMMITTER_DATE_ISO "${GIT_COMMITTER_DATE_ISO}" CACHE INTERNAL "git committer date, strict ISO 8601 format")

  # origin remote url
  execute_process(COMMAND ${GIT_EXECUTABLE} config --get remote.origin.url HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_REMOTE_ORIGIN_URL OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_REMOTE_ORIGIN_URL "${GIT_REMOTE_ORIGIN_URL}" CACHE INTERNAL "git origin remote url")

  # most recent tag of the current branch
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0 HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_LATEST_TAG_LONG OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_LATEST_TAG_LONG "${GIT_LATEST_TAG_LONG}" CACHE INTERNAL "git most recent tag of the current branch")

  # most recent tagname of the current branch
  execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags HEAD
    WORKING_DIRECTORY ${GIT_INFO_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_LATEST_TAG OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(GIT_LATEST_TAG "${GIT_LATEST_TAG}" CACHE INTERNAL "git most recent tagname of the current branch")

endif()


if(GIT_INFO_CMAKE_SHOW)
  message(STATUS "")
  message(STATUS "----------------------------------------------------")
  message(STATUS "                 GitInfo.cmake")
  message(STATUS "")
  message(STATUS "GIT_INFO_SOURCE_DIR : ${GIT_INFO_SOURCE_DIR}")
  message(STATUS "GIT_DIR : ${GIT_DIR}")
  message(STATUS "GIT_FOUND: ${GIT_FOUND}")
  message(STATUS "GIT_EXECUTABLE : ${GIT_EXECUTABLE}")
  message(STATUS "GIT_VERSION_STRING : ${GIT_VERSION_STRING}")
  message(STATUS "")
  message(STATUS "GIT_DIR : ${GIT_DIR}")
  message(STATUS "GIT_IS_DIRTY : ${GIT_IS_DIRTY}")
  message(STATUS "GIT_HEAD_BRANCH : ${GIT_HEAD_BRANCH}")
  message(STATUS "GIT_REVISION : ${GIT_REVISION}")
  message(STATUS "GIT_REVISION_HASH : ${GIT_REVISION_HASH}")
  message(STATUS "GIT_REVISION_NAME : ${GIT_REVISION_NAME}")
  message(STATUS "")
  message(STATUS "GIT_AUTHOR_NAME : ${GIT_AUTHOR_NAME}")
  message(STATUS "GIT_AUTHOR_EMAIL : ${GIT_AUTHOR_EMAIL}")
  message(STATUS "GIT_AUTHOR_DATE : ${GIT_AUTHOR_DATE}")
  message(STATUS "GIT_AUTHOR_DATE_ISO : ${GIT_AUTHOR_DATE_ISO}")
  message(STATUS "")
  message(STATUS "GIT_COMMITTER_NAME : ${GIT_COMMITTER_NAME}")
  message(STATUS "GIT_COMMITTER_EMAIL : ${GIT_COMMITTER_EMAIL}")
  message(STATUS "GIT_COMMITTER_DATE : ${GIT_COMMITTER_DATE}")
  message(STATUS "GIT_COMMITTER_DATE_ISO : ${GIT_COMMITTER_DATE_ISO}")
  message(STATUS "")
  message(STATUS "GIT_REMOTE_ORIGIN_URL : ${GIT_REMOTE_ORIGIN_URL}")
  message(STATUS "GIT_LATEST_TAG_LONG : ${GIT_LATEST_TAG_LONG}")
  message(STATUS "GIT_LATEST_TAG : ${GIT_LATEST_TAG}")
  message(STATUS "")
  message(STATUS "----------------------------------------------------")
  message(STATUS "")
 endif()
