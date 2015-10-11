cmake_minimum_required(VERSION 2.8.11)

project(video)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5WebKit REQUIRED)
find_package(Qt5WebKitWidgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB video_Sources "*.cpp")
file (GLOB video_Headers "*.h")
file (GLOB video_Resources *.qrc)
file (GLOB video_UIS "*.ui")

QT5_ADD_RESOURCES (video_ResourceSources ${video_Resources})
qt5_wrap_ui(video_UI_SRCS ${video_UIS})

add_library( video SHARED ${video_Sources} ${video_Headers} ${video_ResourceSources} ${video_UI_SRCS})

target_link_libraries(video Qt5::Core Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets)
