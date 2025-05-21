cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED True)  

set(OpenCV_DIR "../3rdparty/opencv/build")
find_package(OpenCV REQUIRED)

file(GLOB SOURCE_FILES src/*.cpp) 

add_executable(main ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(main ${OpenCV_LIBS})
install(TARGETS main RUNTIME DESTINATION bin)

