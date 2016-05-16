cmake_minimum_required(VERSION 2.8.11)

project(lightsensor)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB lightsensor_Sources "*.cpp")
file (GLOB lightsensor_Headers "*.h")
file (GLOB lightsensor_Resources *.qrc)
file (GLOB lightsensor_UIS "*.ui")

QT5_ADD_RESOURCES (lightsensor_ResourceSources ${lightsensor_Resources})
qt5_wrap_ui(lightsensor_UI_SRCS ${lightsensor_UIS})

add_library( lightsensor SHARED ${lightsensor_Sources} ${lightsensor_Headers} ${lightsensor_ResourceSources} ${lightsensor_UI_SRCS})

target_link_libraries(lightsensor Qt5::Core Qt5::Widgets hypha::core hypha::plugin )
