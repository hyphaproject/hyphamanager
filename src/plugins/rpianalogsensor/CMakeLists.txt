cmake_minimum_required(VERSION 2.8.11)

project(rpianalogsensor)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB rpianalogsensor_Sources "*.cpp")
file (GLOB rpianalogsensor_Headers "*.h")
file (GLOB rpianalogsensor_Resources *.qrc)
file (GLOB rpianalogsensor_UIS "*.ui")

QT5_ADD_RESOURCES (rpianalogsensor_ResourceSources ${rpianalogsensor_Resources})
qt5_wrap_ui(rpianalogsensor_UI_SRCS ${rpianalogsensor_UIS})

add_library( rpianalogsensor SHARED ${rpianalogsensor_Sources} ${rpianalogsensor_Headers} ${rpianalogsensor_ResourceSources} ${rpianalogsensor_UI_SRCS})

target_link_libraries(rpianalogsensor Qt5::Core Qt5::Widgets )
