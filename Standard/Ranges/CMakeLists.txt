cmake_minimum_required(VERSION 4.1.2)

project("Ranges")
set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Force libc++ only on Linux (where Clang defaults to libstdc++)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
    message(STATUS "Linux detected: Using libc++ for better C++23 ranges support")
endif()

add_executable(ranges views.cpp
        advanced_views.cpp)