cmake_minimum_required(VERSION 2.8.11)

project(rpiled)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB rpiled_Sources "*.cpp")
file (GLOB rpiled_Headers "*.h")
file (GLOB rpiled_Resources *.qrc)
file (GLOB rpiled_UIS "*.ui")

QT5_ADD_RESOURCES (rpiled_ResourceSources ${rpiled_Resources})
qt5_wrap_ui(rpiled_UI_SRCS ${rpiled_UIS})

add_library( rpiled SHARED ${rpiled_Sources} ${rpiled_Headers} ${rpiled_ResourceSources} ${rpiled_UI_SRCS})

target_link_libraries(rpiled Qt5::Core Qt5::Widgets hypha::core hypha::plugin )
