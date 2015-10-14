cmake_minimum_required(VERSION 3.0.0)

project(hyphamanager)
set(PROJECT_NAME "hyphamanager")
set(PROJECT_LONGNAME "Hypha Manager")
set(VERSION "0.1.0")

ADD_DEFINITIONS(
    -std=c++11
)

# Configure Qt
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

if (NOT MSVC)
  # Enable the C++11 standard
  #set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
endif()

# Testing configuration
enable_testing()
set(TEST_LINK_LIBRARIES Qt5::Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/plugins)
if (WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/plugins)
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/plugins)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
if (WIN32)
    set(TRANSLATION_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/i18n)
else()
    set(TRANSLATION_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/i18n)
endif()

option(BUILD_DOCUMENTATION "Create doxygen documentation for developers" OFF)

add_subdirectory( src )
add_subdirectory( doc )

if (WIN32)
  add_subdirectory(win)
endif()
