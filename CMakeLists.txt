
project( echoecho )

cmake_minimum_required(VERSION 2.8.12)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE(Boost 1.55.0 REQUIRED COMPONENTS system filesystem thread)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_thread")

FILE(GLOB HEADERS
        "${PROJECT_SOURCE_DIR}/src/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.h"
)
INCLUDE_DIRECTORIES(
        ${HEADERS}
        ${Boost_INCLUDE_DIRS}
)
include_directories(include)

link_directories(
        ${Boost_LIBRARY_DIRS}
        /usr/local/lib
)

set(CMAKE_VERBOSE_MAKEFILE ON)

#add_subdirectory( src )
FILE(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_library(echo STATIC ${SRC_FILES})

add_executable(echoecho main.cpp)

target_link_libraries(echoecho echo)