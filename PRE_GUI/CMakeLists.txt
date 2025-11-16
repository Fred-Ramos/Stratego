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
    src/piece.h
    src/board.h
    src/game.h
)
set(Sources
    src/piece.cpp
    src/board.cpp
    src/game.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

#look for cmake list inside test folder and run it
add_subdirectory(test)