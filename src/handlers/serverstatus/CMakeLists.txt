cmake_minimum_required(VERSION 2.8.11)

project(serverstatus)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file(GLOB serverstatus_Sources "*.cpp")
file(GLOB serverstatus_Headers "*.h")
file(GLOB serverstatus_Resources "*.qrc")
file(GLOB serverstatus_UIS "*.ui")

QT5_ADD_RESOURCES(serverstatus_ResourceSources ${serverstatus_Resources})
qt5_wrap_ui(serverstatus_UI_SRCS ${serverstatus_UIS})

add_library( serverstatus SHARED ${serverstatus_Sources} ${serverstatus_Headers} ${serverstatus_ResourceSources} ${serverstatus_UI_SRCS})

target_link_libraries(serverstatus Qt5::Core Qt5::Widgets )
