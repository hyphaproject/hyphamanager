cmake_minimum_required(VERSION 2.8.11)

project(blechuhr)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file(GLOB blechuhr_Sources "*.cpp")
file(GLOB blechuhr_Headers "*.h")
file(GLOB blechuhr_Resources "*.qrc")
file (GLOB blechuhr_UIS "*.ui")

QT5_ADD_RESOURCES(blechuhr_ResourceSources ${blechuhr_Resources})
qt5_wrap_ui(blechuhr_UI_SRCS ${blechuhr_UIS})

add_library( blechuhr SHARED ${blechuhr_Sources} ${blechuhr_Headers} ${blechuhr_ResourceSources} ${blechuhr_UI_SRCS} )

target_link_libraries(blechuhr Qt5::Core Qt5::Widgets )
