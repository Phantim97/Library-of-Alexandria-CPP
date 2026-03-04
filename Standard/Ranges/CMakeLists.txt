cmake_minimum_required(VERSION 4.1.2)

project("Ranges")
SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Force libc++ only on Linux (where Clang defaults to libstdc++)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    SET(CMAKE_CXX_COMPILER clang++)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
    message(STATUS "Linux detected: Using libc++ for better C++23 ranges support")
endif()

add_executable(ranges views.cpp)