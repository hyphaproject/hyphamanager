cmake_minimum_required(VERSION 2.8.11)

project(watersensor)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB watersensor_Sources "*.cpp")
file (GLOB watersensor_Headers "*.h")
file (GLOB watersensor_Resources *.qrc)
file (GLOB watersensor_UIS "*.ui")

QT5_ADD_RESOURCES (watersensor_ResourceSources ${watersensor_Resources})
qt5_wrap_ui(watersensor_UI_SRCS ${watersensor_UIS})

add_library( watersensor SHARED ${watersensor_Sources} ${watersensor_Headers} ${watersensor_ResourceSources} ${watersensor_UI_SRCS})

target_link_libraries(watersensor Qt5::Core Qt5::Widgets hypha::core hypha::plugin )
