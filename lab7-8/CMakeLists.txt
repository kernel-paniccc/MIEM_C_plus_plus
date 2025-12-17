cmake_minimum_required(VERSION 3.10)
project(ProcessListLab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app
    main.cpp
    PCB.cpp
    ListNode.cpp
    ProcessList.cpp
)