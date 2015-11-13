cmake_minimum_required(VERSION 2.8)

project(Sur)

set (Sur_VERSION_MAJOR 0)
set (Sur_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -D__STDC_CONSTANT_MACROS")

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

ExternalProject_Add(ffmpeg
  CONFIGURE_COMMAND ${PROJECT_SOURCE_DIR}/libs/ffmpeg/configure --disable-encoders --disable-programs --disable-doc
  BUILD_COMMAND "make"
  INSTALL_COMMAND ""
  BUILD_IN_SOURCE 1
  SOURCE_DIR ${PROJECT_SOURCE_DIR}/libs/ffmpeg
  PREFIX ffmpeg
  INSTALL_COMMAND ""
  )

set(FFMPEG_LIBS libavutil.a libavcodec.a libswscale.a libavdevice.a libavfilter.a libavformat.a libswresample.a)
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavcodec")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavutil")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavdevice")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavfilter")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavformat")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libswresample")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libswscale")

include_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg")

add_executable(Sur ${SOURCES})
target_link_libraries(Sur ${PROJECT_LINK_LIBS})
target_link_libraries(Sur ${FFMPEG_LIBS})
