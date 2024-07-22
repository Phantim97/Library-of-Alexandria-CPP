cmake_minimum_required(VERSION 3.28)
project(InputTest)

set(CMAKE_CXX_STANDARD 23)

find_library(APPLICATION_SERVICES ApplicationServices)

add_executable(InputTest main.cpp)

target_link_libraries(InputTest ${APPLICATION_SERVICES})