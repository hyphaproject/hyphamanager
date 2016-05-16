cmake_minimum_required(VERSION 2.8.11)

project(fingerprintzfm)

find_package(Qt5Core)
find_package(Qt5Widgets REQUIRED)

find_package(Poco COMPONENTS Foundation Util Net Data DataMySQL DataSQLite REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (../../)
file (GLOB fingerprintzfm_Sources "*.cpp")
file (GLOB fingerprintzfm_Headers "*.h")
file (GLOB fingerprintzfm_Resources "*.qrc")
file (GLOB fingerprintzfm_UIS "*.ui")

QT5_ADD_RESOURCES (fingerprintzfm_ResourceSources ${fingerprintzfm_Resources})
qt5_wrap_ui(fingerprintzfm_UI_SRCS ${fingerprintzfm_UIS})

add_library( fingerprintzfm SHARED ${fingerprintzfm_Sources} ${fingerprintzfm_Headers} ${fingerprintzfm_ResourceSources} ${fingerprintzfm_UI_SRCS})

target_link_libraries(fingerprintzfm Qt5::Core Qt5::Widgets hypha::core hypha::plugin )
