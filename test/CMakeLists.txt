cmake_minimum_required(VERSION 3.28)

set(This alltests)

set(Headers
    testfunctions.h
)
set(Sources
    testfunctions.cpp
    0Spy_test.cpp
    1Scout_test.cpp
    2Miner_test.cpp
    Gameover_test.cpp
)

add_executable(${This} ${Sources} ${Headers})
target_link_libraries(${This} PUBLIC
    gtest_main
    Piece_test
)

add_test(
    NAME ${This}
    COMMAND ${This}
)