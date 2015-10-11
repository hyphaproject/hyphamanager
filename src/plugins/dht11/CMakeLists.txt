cmake_minimum_required(VERSION 2.8.11)

project(dht11)
find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB dht11_Sources "*.cpp")
file (GLOB dht11_Headers "*.h")
file (GLOB dht11_Resources *.qrc)
file (GLOB dht11_UIS "*.ui")

QT5_ADD_RESOURCES (dht11_ResourceSources ${dht11_Resources})
qt5_wrap_ui(dht11_UI_SRCS ${dht11_UIS})

add_library( dht11 SHARED ${dht11_Sources} ${dht11_Headers} ${dht11_ResourceSources} ${dht11_UI_SRCS})

target_link_libraries(dht11 Qt5::Core Qt5::Widgets )
