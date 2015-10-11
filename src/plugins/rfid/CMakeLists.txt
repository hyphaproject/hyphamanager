cmake_minimum_required(VERSION 2.8.11)

project(rfid)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB rfid_Sources "*.cpp")
file (GLOB rfid_Headers "*.h")
file (GLOB rfid_Resources "*.qrc")
file (GLOB rfid_UIS "*.ui")

QT5_ADD_RESOURCES (rfid_ResourceSources ${rfid_Resources})
qt5_wrap_ui(rfid_UI_SRCS ${rfid_UIS})

add_library( rfid SHARED ${rfid_Sources} ${rfid_Headers} ${rfid_ResourceSources} ${rfid_UI_SRCS})

target_link_libraries(rfid Qt5::Core Qt5::Widgets )
