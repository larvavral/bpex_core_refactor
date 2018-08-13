cmake_minimum_required(VERSION 3.10.2)

project(BPEX)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

ADD_DEFINITIONS(/D_DEBUG)

include_directories(include)
include_directories(src)
#include_directories(include/boost/)

link_directories(lib)
#set (PROJECT_LINK_LIBS event hiredis event_core boost_program_options pthread )
# Use libhiredis.
set(PROJECT_LINK_LIBS event libhiredis.a)

file(GLOB CPP_SOURCES "src/*.cc")
file(GLOB COMMON_SOURCES "src/common/*.cc")
file(GLOB REDIS_SOURCES "src/redis/*.cc")
add_executable(BPEX ${CPP_SOURCES} ${COMMON_SOURCES} ${REDIS_SOURCES})

target_link_libraries(BPEX ${PROJECT_LINK_LIBS})
