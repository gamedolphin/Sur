cmake_minimum_required(VERSION 2.8)

project(Sur)

set (Sur_VERSION_MAJOR 0)
set (Sur_VERSION_MINOR 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -D__STDC_CONSTANT_MACROS")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

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
  CONFIGURE_COMMAND ${PROJECT_SOURCE_DIR}/libs/ffmpeg/configure --disable-debug --disable-avdevice --disable-avfilter --disable-swscale --enable-ffmpeg --disable-ffplay --disable-ffserver --disable-network --disable-muxers --disable-demuxers --enable-rdft --enable-demuxer=aac --enable-demuxer=ac3 --enable-demuxer=ape --enable-demuxer=asf --enable-demuxer=flac --enable-demuxer=matroska_audio --enable-demuxer=mp3 --enable-demuxer=mpc --enable-demuxer=mov --enable-demuxer=mpc8 --enable-demuxer=ogg --enable-demuxer=tta --enable-demuxer=wav --enable-demuxer=wv --disable-bsfs --disable-filters --disable-parsers  --enable-parser=aac --enable-parser=ac3 --enable-parser=mpegaudio --disable-protocols --enable-protocol=file --disable-indevs --disable-outdevs --disable-encoders --disable-decoders --enable-decoder=aac --enable-decoder=ac3 --enable-decoder=alac --enable-decoder=ape --enable-decoder=flac --enable-decoder=mp1 --enable-decoder=mp2 --enable-decoder=mp3 --enable-decoder=mpc7 --enable-decoder=mpc8 --enable-decoder=tta --enable-decoder=vorbis --enable-decoder=wavpack --enable-decoder=wmav1 --enable-decoder=wmav2 --enable-decoder=pcm_alaw --enable-decoder=pcm_dvd  --enable-decoder=pcm_f32be --enable-decoder=pcm_f32le --enable-decoder=pcm_f64be --enable-decoder=pcm_f64le --enable-decoder=pcm_s16be --enable-decoder=pcm_s16le --enable-decoder=pcm_s16le_planar --enable-decoder=pcm_s24be --enable-decoder=pcm_daud --enable-decoder=pcm_s24le --enable-decoder=pcm_s32be --enable-decoder=pcm_s32le --enable-decoder=pcm_s8 --enable-decoder=pcm_u16be --enable-decoder=pcm_u16le --enable-decoder=pcm_u24be --enable-decoder=pcm_u24le --enable-decoder=rawvideo
  BUILD_COMMAND "make"
  INSTALL_COMMAND ""
  BUILD_IN_SOURCE 1
  SOURCE_DIR ${PROJECT_SOURCE_DIR}/libs/ffmpeg
  PREFIX ffmpeg
  INSTALL_COMMAND ""
  )

set(FFMPEG_LIBS libavformat.a libavcodec.a libavutil.a libavdevice.a libavfilter.a libswresample.a)
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavcodec")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavutil")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavdevice")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavfilter")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libavformat")
link_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg/libswresample")

include_directories("${PROJECT_SOURCE_DIR}/libs/ffmpeg")

add_executable(Sur ${SOURCES})
add_dependencies(Sur ffmpeg libsoundio)
target_link_libraries(Sur ${PROJECT_LINK_LIBS})
target_link_libraries(Sur ${FFMPEG_LIBS})

find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
  include_directories( ${ZLIB_INCLUDE_DIRS} )
  target_link_libraries( Sur ${ZLIB_LIBRARIES} )
endif( ZLIB_FOUND )
