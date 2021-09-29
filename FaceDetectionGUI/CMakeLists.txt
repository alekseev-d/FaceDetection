cmake_minimum_required(VERSION 3.18)
project(FaceDetectionGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/form)

find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/form)

set (PROJECT_LINK_LIBS ${CMAKE_CURRENT_BINARY_DIR}/libTevianDLL.dll)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dll/libTevianDLL.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/json_parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/face_info.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/teviandll.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/teviandll_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/zoom_view.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/auth_window.h
    )

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/json_parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/zoom_view.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/auth_window.cpp
    )

set(UI
    ${CMAKE_CURRENT_SOURCE_DIR}/form/auth_window.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/form/mainwindow.ui
    )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/icon/icon.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_executable(FaceDetectionGUI ${SOURCES} ${UI} ${HEADERS})

target_link_libraries(FaceDetectionGUI Qt5::Core Qt5::Gui Qt5::Network Qt5::Widgets)
target_link_libraries(FaceDetectionGUI ${PROJECT_LINK_LIBS})
