cmake_minimum_required(VERSION 2.8.11)

project(espeak)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

find_package(Poco COMPONENTS Foundation Util Net Data DataMySQL DataSQLite REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB espeak_Sources "*.cpp")
file (GLOB espeak_Headers "*.h")
file (GLOB espeak_Resources *.qrc)
file (GLOB espeak_UIS "*.ui")

QT5_ADD_RESOURCES (espeak_ResourceSources ${espeak_Resources})
qt5_wrap_ui(espeak_UI_SRCS ${espeak_UIS})

add_library( espeak SHARED ${espeak_Sources} ${espeak_Headers} ${espeak_ResourceSources} ${espeak_UI_SRCS})

target_link_libraries(espeak Qt5::Core Qt5::Widgets hypha::core hypha::plugin )
