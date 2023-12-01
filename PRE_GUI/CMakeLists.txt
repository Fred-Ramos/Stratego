cmake_minimum_required(VERSION 3.28)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

set(This Stratego_test)

project(${This} CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

#look for cmake list inside googletest folder and run it
add_subdirectory(googletest)

set(Headers
    logic/piece.h
    logic/board.h
    logic/game.h
)
set(Sources
    logic/piece.cpp
    logic/board.cpp
    logic/game.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

#look for cmake list inside test folder and run it
add_subdirectory(test)