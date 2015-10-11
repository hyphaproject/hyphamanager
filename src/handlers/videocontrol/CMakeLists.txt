cmake_minimum_required(VERSION 2.8.11)

project(videocontrol)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file(GLOB videocontrol_Sources "*.cpp")
file(GLOB videocontrol_Headers "*.h")
file(GLOB videocontrol_Resources "*.qrc")
file(GLOB videocontrol_UIS "*.ui")

QT5_ADD_RESOURCES(videocontrol_ResourceSources ${videocontrol_Resources})
qt5_wrap_ui(videocontrol_UI_SRCS ${videocontrol_UIS})

add_library( videocontrol SHARED ${videocontrol_Sources} ${videocontrol_Headers} ${videocontrol_ResourceSources} ${videocontrol_UI_SRCS})

target_link_libraries(videocontrol Qt5::Core Qt5::Widgets )
