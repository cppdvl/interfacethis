cmake_minimum_required(VERSION 3.5)

project(iface_show CXX)

#Debug Project with C++ 20
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(EXPORT_COMPILE_COMMANDS ON)




add_executable(ifaceshow main.cpp)


