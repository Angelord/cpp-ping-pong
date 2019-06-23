cmake_minimum_required(VERSION 3.14)
project(cpp_ping_pong)

set(CMAKE_CXX_STANDARD 14)

include_directories(Includes/SDL)

add_executable(cpp_ping_pong
        Source/main.cpp
        Source/Game.cpp
        Source/Vector2.cpp
        Source/Timer.cpp
        )

target_link_libraries(cpp_ping_pong
        "-framework SDL2"
        )