cmake_minimum_required(VERSION 3.15)
project(shark-boy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/raylib)

file(GLOB SRC_FILES src/*.cpp)

add_executable(game ${SRC_FILES})

target_include_directories(game PRIVATE
    include              
    lib/raylib/src      
)

target_link_libraries(game PRIVATE raylib)
