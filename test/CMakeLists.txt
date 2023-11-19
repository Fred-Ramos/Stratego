cmake_minimum_required(VERSION 3.28)

set(This alltests)

set(Headers
    testfunctions.h
)
set(Sources
    testfunctions.cpp
    Scout_test.cpp
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