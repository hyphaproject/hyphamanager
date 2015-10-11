cmake_minimum_required(VERSION 2.8.11)

project(email)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB email_Sources "*.cpp")
file (GLOB email_Headers "*.h")
file (GLOB email_Resources *.qrc)
file (GLOB email_UIS "*.ui")

QT5_ADD_RESOURCES (email_ResourceSources ${email_Resources})
qt5_wrap_ui(email_UI_SRCS ${email_UIS})

add_library( email SHARED ${email_Sources} ${email_Headers} ${email_ResourceSources} ${email_UI_SRCS})

target_link_libraries(email Qt5::Core Qt5::Widgets )
