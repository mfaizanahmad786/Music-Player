cmake_minimum_required(VERSION 3.29)
project(PlaybackManagment)

set(CMAKE_CXX_STANDARD 20)

add_executable(PlaybackManagment main.cpp
        Queue.h
        Queue.cpp
        Song.cpp)
