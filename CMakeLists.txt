cmake_minimum_required(VERSION 3.20)
project(calculator)

find_package(Catch2 REQUIRED)

include_directories(src)
file(GLOB SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

add_library(prog ${SOURCES})

add_executable(calc src/main.cpp)
add_executable(tests ${TEST_SOURCES})

target_link_libraries(calc prog)
target_link_libraries(tests prog)

set_property(TARGET calc tests PROPERTY CXX_STANDARD 17)
set_property(TARGET calc tests PROPERTY CXX_STANDARD_REQUIRED 17)

include(CTest)
include(Catch)
catch_discover_tests(tests)
