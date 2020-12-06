### Setup project ##############################################################

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(AdventOfCode2020 VERSION 1.0 LANGUAGES CXX)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

### Build types ################################################################

set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
		STRING "Choose the type of build." FORCE)

	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
		"Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

### Executable #################################################################

set(SOURCE_FILES
	src/main.cpp
	src/files.cpp
	src/input.cpp

	src/day_1.cpp
	src/day_2.cpp
	src/day_3.cpp
	src/day_4.cpp
	src/day_5.cpp
	src/day_6.cpp
)

add_executable(aoc2020 ${SOURCE_FILES})

target_include_directories(aoc2020 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_features(aoc2020 PRIVATE cxx_std_17)
set_target_properties(aoc2020 PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
)
