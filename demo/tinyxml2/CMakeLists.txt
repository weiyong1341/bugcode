cmake_minimum_required(VERSION 3.4)
project( example )


set(TINYXML2_INCLUDE_DIR "../3rd//tinyxml2/include")
set(TINYXML2_LIB_DIR "../3rd/tinyxml2_demo/tinyxml2/lib")

include_directories(${tinyxml2_INCLUDE_DIRS} )
link_directories(${TINYXML2_LIB_DIR})

add_executable( example example.cpp )

target_include_directories(example PUBLIC ${TINYXML2_INCLUDE_DIR})
target_link_libraries( example PUBLIC tinyxml2)
