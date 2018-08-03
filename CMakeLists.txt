cmake_minimum_required(VERSION 3.10.2)

project (BPEX)

set (CMAKE_CXX_STANDARD 11)

include_directories(include)
#include_directories(src)
#include_directories(include/boost/)

link_directories(lib)
#set ( PROJECT_LINK_LIBS event hiredis event_core boost_program_options pthread )

file(GLOB CPP_SOURCES "src/*.cpp")
add_executable(BPEX ${CPP_SOURCES})

#target_link_libraries(BPEX ${PROJECT_LINK_LIBS} )
