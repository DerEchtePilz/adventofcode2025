cmake_minimum_required(VERSION 4.0)
project(adventofcode2025)

set(CMAKE_CXX_STANDARD 23)

add_executable(adventofcode2025 main.cpp
        src/util.h
        src/day1.h
        main.h
        src/day2.h
        src/day3.h
        src/day4.h
        src/day5.h
        src/day6.h
        src/day7.h)
