cmake_minimum_required(VERSION 3.10)
project(battleship C)

set(CMAKE_C_STANDARD 99)

add_executable(battleship battleship.c libraries/battleship_librarie.c)
target_include_directories(battleship PRIVATE libraries)
