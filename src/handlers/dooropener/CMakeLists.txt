cmake_minimum_required(VERSION 2.8.11)

project(dooropener)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file(GLOB dooropener_Sources "*.cpp" "../../database/database.cpp" "../../settings/databasesettings.cpp" "../../settings/hyphamanagersettings.cpp" )
file(GLOB dooropener_Headers "*.h" "../../database/database.h" "../../settings/databasesettings.h" "../../settings/hyphamanagersettings.h" )
file(GLOB dooropener_Resources "*.qrc")
file(GLOB dooropener_UIS "*.ui")

QT5_ADD_RESOURCES(dooropener_ResourceSources ${dooropener_Resources})
qt5_wrap_ui(dooropener_UI_SRCS ${dooropener_UIS})

add_library( dooropener SHARED ${dooropener_Sources} ${dooropener_Headers} ${dooropener_ResourceSources} ${dooropener_UI_SRCS})

target_link_libraries(dooropener Qt5::Core Qt5::Widgets Qt5::Sql Qt5::Network)
