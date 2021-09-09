cmake_minimum_required(VERSION 3.19)
project(mysat)

set(CMAKE_CXX_STANDARD 14)

add_executable(mysat main.cpp DPLL.cpp global.h file.cpp clause.cpp global.cpp sudu.cpp)
