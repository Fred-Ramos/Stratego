cmake_minimum_required(VERSION 3.28)

set(This Scout_test)

set(Sources
    Scout_test.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    Piece_test
)

add_test(
    NAME ${This}
    COMMAND ${This}
)