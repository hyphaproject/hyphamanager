cmake_minimum_required(VERSION 2.8.11)

project(rpipir)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB rpipir_Sources "*.cpp")
file (GLOB rpipir_Headers "*.h")
file (GLOB rpipir_Resources *.qrc)
file (GLOB rpipir_UIS "*.ui")

QT5_ADD_RESOURCES (rpipir_ResourceSources ${rpipir_Resources})
qt5_wrap_ui(rpipir_UI_SRCS ${rpipir_UIS})

add_library( rpipir SHARED ${rpipir_Sources} ${rpipir_Headers} ${rpipir_ResourceSources} ${rpipir_UI_SRCS})

target_link_libraries(rpipir Qt5::Core Qt5::Widgets hypha::core hypha::plugin )
