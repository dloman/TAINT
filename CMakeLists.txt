cmake_minimum_required(VERSION 3.0)

project(TAINT)
set(MODULE_NAME TAINT)
add_definitions(-DMODULE_NAME=\"TAINT\")

add_definitions(-Wall)
add_definitions(-fPIC)

set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
set(CMAKE_C_COMPILER /usr/local/bin/gcc)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX17)
if(COMPILER_SUPPORTS_CXX17)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
  add_definitions(-std=c++1z)
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support.
    Please use a different C++ compiler.")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Threads)

MESSAGE("!!!!!!!!!!!!!  ${CMAKE_INSTALL_PREFIX}/lib/DanLib-0.1")
find_package(DanLib REQUIRED HINTS ${DanLib_DIR})

include_directories(${DanLib_INCLUDE_DIR})
MESSAGE("!!!!!!!!!!!!!!!! ${DanLib_INCLUDE_DIR}/Requests")

OPTION(USE_BOOST_DLL "Use Boost DLLs" ON)

IF (USE_BOOST_DLL)
  SET(Boost_USE_STATIC_LIBS OFF)
  ADD_DEFINITIONS(-DBOOST_ALL_DYN_LINK)
ELSE()
  SET(Boost_USE_STATIC_LIBS ON)
ENDIF()

SET(BOOST_LIBRARYDIR /usr/local/lib)
SET(BOOST_ROOT /usr/local)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

include_directories(src)

set(CMAKE_DEBUG_POSTFIX d)

add_library(
  TaintLib
  src/PanelImageMaker.cpp
  src/PanelImageMaker.hpp
  )

target_link_libraries(
  TaintLib
  Requests
  Image
  )

add_executable(
  TAINT
  src/Taint.cpp
  )

target_link_libraries(
  TAINT
  TaintLib
  )

add_executable(
  ImageServer
  src/ImageServer.cpp
  )

target_link_libraries(
  ImageServer
  TaintLib
  String
  Tcp
  )
