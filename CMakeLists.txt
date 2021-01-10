cmake_minimum_required(VERSION 3.17)
project(bridge-tcp-serial VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(bridge-host)
add_subdirectory(bridge-arduino)