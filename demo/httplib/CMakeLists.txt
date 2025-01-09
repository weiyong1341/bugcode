cmake_minimum_required(VERSION 3.4)
project( example )

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(example example.cpp)

target_include_directories(example PRIVATE "./")
target_link_libraries(example PRIVATE Threads::Threads)
