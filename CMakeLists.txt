cmake_minimum_required(VERSION 3.16)

project(Soundgenerator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

qt_add_executable(Soundgenerator
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    soundgenerator.cpp
    soundgenerator.h
)

target_link_libraries(Soundgenerator PRIVATE
    Qt6::Widgets
    Qt6::Multimedia
)

install(TARGETS Soundgenerator
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)
