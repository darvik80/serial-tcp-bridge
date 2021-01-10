cmake_minimum_required(VERSION 3.17)
project(bridge-host VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCS_G
        src/main.cpp.cpp
        src/BridgeEncoder.cpp
        src/BridgeDecoder.cpp
        )

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../bridge-arduino/include
)
add_definitions(-DBOOST_LOG_DYN_LINK)

find_package(Boost REQUIRED COMPONENTS system program_options filesystem thread log log_setup)
find_package(Threads)

link_directories(
        /usr/local/lib
)

add_executable(bridge-host ${SRCS_G})

target_link_libraries(bridge-host ${Boost_LIBRARIES})
