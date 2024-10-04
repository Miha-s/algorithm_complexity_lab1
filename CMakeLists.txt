cmake_minimum_required(VERSION 3.20)

project(hashing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")


file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

find_package(GMP REQUIRED)

if(GMP_FOUND)
    include_directories(${GMP_INCLUDES})
else()
    message(FATAL_ERROR "GMP library not found")
endif()


add_executable(hashing main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(hashing ${GMP_LIBRARIES})

target_include_directories(hashing PUBLIC ./src)

