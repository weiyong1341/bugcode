cmake_minimum_required(VERSION 3.4)
project( example )
set(CMAKE_CXX_STANDARD 11)

include_directories("/root/workspace/ffmpeg_demo/ffmpeg/include")
link_directories("/root/workspace/ffmpeg_demo/ffmpeg/lib")

add_executable( example example.cpp )
target_link_libraries( example avcodec avformat)