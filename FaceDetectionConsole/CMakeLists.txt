cmake_minimum_required(VERSION 3.18)

project(FaceDetectionConsole LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (PROJECT_LINK_LIBS ${CMAKE_CURRENT_BINARY_DIR}/libTevianDLL.dll)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dll/libTevianDLL.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/json_parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/face_info.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/teviandll.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/teviandll_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/tevian_console.h
    )

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/json_parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tevian_console.cpp
    )

add_executable(FaceDetectionConsole ${SOURCES} ${HEADERS})

target_link_libraries(FaceDetectionConsole Qt5::Core Qt5::Network)
target_link_libraries(FaceDetectionConsole ${PROJECT_LINK_LIBS})
