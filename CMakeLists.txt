cmake_minimum_required(VERSION 3.16)
project(PID_Controller)

set(CMAKE_CXX_STANDARD 14)

add_executable(PID_Controller PID/pid.cpp PID/pid.h PID/run_pid.cpp PID/run_pid.h main.cpp)