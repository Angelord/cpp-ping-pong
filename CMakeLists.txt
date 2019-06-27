cmake_minimum_required(VERSION 3.14)
project(ping_pong)

set(CMAKE_CXX_STANDARD 14)

# Find SDL2
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Modules")
find_package(SDL2 REQUIRED COMPONENTS main)
include_directories(${SDL2_INCLUDE_DIRS} Source)

add_executable(ping_pong
        Source/main.cpp
        Source/Game.cpp
        Source/Vector2.cpp
        Source/Timer.cpp
        Source/Beeper.cpp
        )

target_link_libraries(ping_pong ${SDL2_LIBS} )

# Copy SDL2 DLLs to output folder on Windows
if(WIN32)
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET ping_pong POST_BUILD COMMAND
                ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:ping_pong>)
    endforeach()
endif()