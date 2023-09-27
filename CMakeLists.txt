cmake_minimum_required(VERSION 3.26)
project(A1Cmake)

set(CMAKE_CXX_STANDARD 17)

add_executable(MainDriver main.cpp
        src/Map/MapDriver.cpp src/Map/Map.cpp src/Map/Map.h
        src/Map/MapDriver.cpp src/Map/MapDriver.h)