cmake_minimum_required(VERSION 3.0.0)
project(hyphamanager)
file (STRINGS "${PROJECT_SOURCE_DIR}/VERSION" PACKAGE_VERSION )
string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MAJOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9])+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MINOR ${PACKAGE_VERSION})
string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" CPACK_PACKAGE_VERSION_PATCH ${PACKAGE_VERSION})
set(COMPLETE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
set(RELEASE_NAME "Unstable-trunk")
set(PROJECT_VERSION ${COMPLETE_VERSION})

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

if (CMAKE_BUILD_TYPE STREQUAL "")
    set( CMAKE_BUILD_TYPE "RelWithDebInfo" )
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

#############################################################
# Enable packaging
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Hypha Manager")
set(CPACK_PACKAGE_VENDOR "chriamue")
set(CPACK_PACKAGE_CONTACT "chriamue")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr/local")
set(CPACK_PACKAGE_VERSION ${COMPLETE_VERSION})
set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
set (CPACK_PACKAGE_FILE_NAME   "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_DEBIAN_ARCHITECTURE}")
include(CPack)
#############################################################

add_subdirectory( src )
add_subdirectory( doc )

if (WIN32)
  add_subdirectory(win)
endif()
