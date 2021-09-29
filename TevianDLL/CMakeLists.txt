cmake_minimum_required(VERSION 3.18)
project(TevianDLL)

set(CMAKE_AUTOMOC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt5 COMPONENTS Core Network REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tevian_dll.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tevian_dll_global.h
    )

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tevian_dll.cpp
)

add_library(TevianDLL SHARED ${SOURCES} ${HEADERS})

target_link_libraries(TevianDLL Qt5::Core Qt5::Network)

target_compile_definitions(TevianDLL PRIVATE TEVIANDLL_LIBRARY)

