cmake_minimum_required(VERSION 3.13)
project(clionHash)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)

add_executable(clionHash
        main.cpp
        Hashish.cpp
        skGeneratorius.cpp
        includes/hashish.h
        )