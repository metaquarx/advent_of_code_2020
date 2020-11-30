### Setup project ##############################################################

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(FILL_PROJECT_NAME VERSION 1.0 LANGUAGES CXX)

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

### Library ####################################################################

set(SOURCE_FILES
	src/FILL_FILES.cpp
)

add_library(FILL_LIBRARY_NAME ${SOURCE_FILES})

target_include_directories(FILL_LIBRARY_NAME PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(FILL_LIBRARY_NAME PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_features(FILL_LIBRARY_NAME PRIVATE cxx_std_17)
set_target_properties(FILL_LIBRARY_NAME PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
)

if(CMAKE_PROJECT_NAME STREQUAL FILL_LIBRARY_NAME)
	include(CTest)
	add_subdirectory(test)
endif()

### Executable #################################################################

set(SOURCE_FILES
	src/FILL_FILES.cpp
)

add_executable(FILL_EXECUTABLE_NAME ${SOURCE_FILES})

target_include_directories(FILL_EXECUTABLE_NAME PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_compile_features(FILL_EXECUTABLE_NAME PRIVATE cxx_std_17)
set_target_properties(FILL_EXECUTABLE_NAME PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
)
