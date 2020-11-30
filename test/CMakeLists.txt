### Setup project ##############################################################

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(FILL_PROJECT_NAMETests LANGUAGES CXX)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

### Test #######################################################################

set(TEST_FILES
	test.cpp
)

add_executable(Tests ${TEST_FILES})
target_link_libraries(Tests PRIVATE FILL_LIBRARY_NAME)

### Catch2 #####################################################################

find_package(Catch2 REQUIRED)
include(Catch)

target_link_libraries(Tests PRIVATE Catch2::Catch2)

catch_discover_tests(Tests)
