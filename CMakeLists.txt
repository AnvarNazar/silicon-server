cmake_minimum_required(VERSION 3.15)
project(silicon)

set(CMAKE_CXX_STANDARD 14)

add_executable(silicon main.cpp Server.cpp Server.h SiliconException.cpp SiliconException.h ExceptionCodes.h)
add_executable(test-tcp test_tcp.cpp)