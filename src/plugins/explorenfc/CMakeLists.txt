cmake_minimum_required(VERSION 2.8.11)

project(explorenfc)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

find_package(Poco COMPONENTS Foundation Util Net Data DataMySQL DataSQLite REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB explorenfc_Sources "*.cpp")
file (GLOB explorenfc_Headers "*.h")
file (GLOB explorenfc_Resources *.qrc)
file (GLOB explorenfc_UIS "*.ui")

QT5_ADD_RESOURCES (explorenfc_ResourceSources ${explorenfc_Resources})
qt5_wrap_ui(explorenfc_UI_SRCS ${explorenfc_UIS})

add_library( explorenfc SHARED ${explorenfc_Sources} ${explorenfc_Headers} ${explorenfc_ResourceSources} ${explorenfc_UI_SRCS})

target_link_libraries(explorenfc Qt5::Core Qt5::Widgets hypha::core hypha::plugin )
