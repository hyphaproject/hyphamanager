cmake_minimum_required(VERSION 2.8.11)

project(alarm)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file(GLOB alarm_Sources "*.cpp")
file(GLOB alarm_Headers "*.h")
file(GLOB alarm_Resources "*.qrc")
file(GLOB alarm_UIS "*.ui")

QT5_ADD_RESOURCES(alarm_ResourceSources ${alarm_Resources})
qt5_wrap_ui(alarm_UI_SRCS ${alarm_UIS})

add_library( alarm SHARED ${alarm_Sources} ${alarm_Headers} ${alarm_ResourceSources} ${alarm_UI_SRCS})

target_link_libraries(alarm Qt5::Core Qt5::Widgets hypha::core hypha::plugin hypha::handler)
