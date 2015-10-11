cmake_minimum_required(VERSION 2.8.11)

project(flame)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB flame_Sources "*.cpp")
file (GLOB flame_Headers "*.h")
file (GLOB flame_Resources *.qrc)
file (GLOB flame_UIS "*.ui")

QT5_ADD_RESOURCES (flame_ResourceSources ${flame_Resources})
qt5_wrap_ui(flame_UI_SRCS ${flame_UIS})

add_library( flame SHARED ${flame_Sources} ${flame_Headers} ${flame_ResourceSources} ${flame_UI_SRCS})

target_link_libraries(flame Qt5::Core Qt5::Widgets )
