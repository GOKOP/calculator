cmake_minimum_required(VERSION 3.20)
project(calculator)

find_package(Catch2)

include_directories(src)
file(GLOB SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

add_library(prog ${SOURCES})

add_executable(calc src/main.cpp)
target_link_libraries(calc prog)
set_target_properties(calc PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED 17)

if(Catch2_FOUND)
	add_executable(tests ${TEST_SOURCES})
	target_link_libraries(tests prog)
	set_target_properties(tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED 17)

	include(CTest)
	include(Catch)
	catch_discover_tests(tests)
endif()