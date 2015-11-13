cmake_minimum_required(VERSION 2.8)

project(Sur)

set (Sur_VERSION_MAJOR 0)
set (Sur_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11")

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

include(ExternalProject)
ExternalProject_Add( libsoundio
  SOURCE_DIR ${PROJECT_SOURCE_DIR}/libs/libsoundio
  PREFIX libsoundio
  INSTALL_COMMAND ""
  BINARY_DIR ${PROJECT_BINARY_DIR}/libsoundio/build
)


set ( PROJECT_LINK_LIBS libsoundio.so )
link_directories("${PROJECT_BINARY_DIR}/libsoundio/build")


add_executable(Sur ${SOURCES})
target_link_libraries(Sur ${PROJECT_LINK_LIBS})
