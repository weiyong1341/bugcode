cmake_minimum_required(VERSION 3.4)
project( example )

set(OpenCV_DIR "/root/workspace/opencv_demo/opencv/lib/cmake/opencv4")
find_package( OpenCV REQUIRED PATHS)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable( example example.cpp )
target_link_libraries( example ${OpenCV_LIBS} )