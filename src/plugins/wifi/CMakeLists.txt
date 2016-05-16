cmake_minimum_required(VERSION 2.8.11)

project(wifi)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB wifi_Sources "*.cpp")
file (GLOB wifi_Headers "*.h")
file (GLOB wifi_Resources "*.qrc")
file (GLOB wifi_UIS "*.ui")

QT5_ADD_RESOURCES (wifi_ResourceSources ${wifi_Resources})
qt5_wrap_ui(wifi_UI_SRCS ${wifi_UIS})

add_library( wifi SHARED ${wifi_Sources} ${wifi_Headers} ${wifi_ResourceSources} ${wifi_UI_SRCS})

target_link_libraries(wifi Qt5::Core Qt5::Widgets hypha::core hypha::plugin )
