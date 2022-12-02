cmake_minimum_required(VERSION 3.20)
project(calculator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)
file(GLOB SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

add_library(prog ${SOURCES})
set_target_properties(prog PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED 20)

add_executable(calc src/main.cpp)
target_link_libraries(calc prog)
set_target_properties(calc PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED 20)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests prog)
set_target_properties(tests PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED 20)
