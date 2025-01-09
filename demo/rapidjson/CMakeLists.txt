cmake_minimum_required(VERSION 3.4)
project( example )

set(RAPIDJSON_INCLUDE_DIRS /root/workspace/rapidjson_demo/rapidjson/include)
include_directories(${RAPIDJSON_INCLUDE_DIRS})

add_executable( example example.cpp )
