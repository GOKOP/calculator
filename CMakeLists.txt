cmake_minimum_required(VERSION 3.20)
project(calculator)

include_directories(src)
file(GLOB SOURCES "src/*.cpp")
add_executable(calc ${SOURCES})
set_property(TARGET calc PROPERTY CXX_STANDARD 17)
set_property(TARGET calc PROPERTY CXX_STANDARD_REQUIRED 17)
