cmake_minimum_required(VERSION 3.20)
project(gba-plusplus)

set(CMAKE_MODULE_PATH "docs/cmake" ${CMAKE_MODULE_PATH})

add_library(gba-plusplus INTERFACE)
target_include_directories(gba-plusplus INTERFACE include/)
set_target_properties(gba-plusplus PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(docs)
