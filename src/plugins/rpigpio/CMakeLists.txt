cmake_minimum_required(VERSION 2.8.11)

project(rpigpio)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB rpigpio_Sources "*.cpp")
file (GLOB rpigpio_Headers "*.h")
file (GLOB rpigpio_Resources *.qrc)
file (GLOB rpigpio_UIS "*.ui")

QT5_ADD_RESOURCES (rpigpio_ResourceSources ${rpigpio_Resources})
QT5_WRAP_UI(rpigpio_UI_SRCS ${rpigpio_UIS})


add_library( rpigpio SHARED ${rpigpio_Sources} ${rpigpio_Headers} ${rpigpio_ResourceSources} ${rpigpio_UI_SRCS})

target_link_libraries(rpigpio Qt5::Core Qt5::Widgets )
